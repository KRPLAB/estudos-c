// bibliotecas padrão
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

// bibliotecas do projeto
#include "../../include/common.h"
#include "../../include/network.h"
#include "../../include/utils.h"

int net_tcp_setup(net_ctx_t *ctx, int port) {
	int opt = 1;

	ctx->port = port;
	ctx->server_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (ctx->server_socket < 0) {
		perror("[TCP_SETUP_ERROR] Falha ao criar socket TCP");
		return -1;
	}

	// Permite reutilizar a porta imediatamente após o fechamento
	if (setsockopt(ctx->server_socket, SOL_SOCKET, SO_REUSEADDR, &opt,
				   sizeof(opt)) < 0) {
		perror("[TCP_SETUP_ERROR] Falha ao configurar socket TCP");
		return -1;
	}

	// Configura endereço do servidor
	struct sockaddr_in server_addr = {.sin_family = AF_INET,
									  .sin_addr.s_addr = INADDR_ANY,
									  .sin_port = htons(port)};

	if (bind(ctx->server_socket, (struct sockaddr *)&server_addr,
			 sizeof(server_addr)) < 0) {
		perror("[TCP_SETUP_ERROR] Erro ao associar socket ao endereço");
		return -1;
	}

	if (listen(ctx->server_socket, 10) < 0) {
		perror("[TCP_SETUP_ERROR] Erro ao iniciar escuta TCP");
		return -1;
	}

	printf("[TCP] TCP Socket pronto na porta %d\n", port);
	return 0;
}

void net_tcp_run(net_ctx_t *ctx, int client_socket,
				 struct sockaddr_in client_addr, socklen_t client_len,
				 char *buffer) {
	ctx->running = 1;
	printf("[TCP] Servidor aguardando conexões na porta %d...\n", ctx->port);

	while (ctx->running) {
		// Aceita conexão do cliente (bloqueante)
		client_socket = accept(ctx->server_socket,
							   (struct sockaddr *)&client_addr, &client_len);

		if (client_socket < 0) {
			perror("[TCP_ERROR] Erro ao aceitar conexão");
			continue;
		}

		// Configura timeout de recepção para evitar bloqueio indefinido
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;

		if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
			perror("[TCP_ERROR] Falha ao configurar timeout no cliente");
		}

		// Recebe requisição do cliente
		int bytes_recebidos = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
		if (bytes_recebidos < 0) {
			perror("[TCP ERROR] Falha ao receber dados (recv retornou -1\n)");
			close(client_socket);
			continue;
		} else if (bytes_recebidos == 0) {
			printf("[TCP] Cliente fechou a conexão inesperadamente.\n");
			close(client_socket);
			continue;
		}

		buffer[bytes_recebidos] = '\0';

		// Exibe requisição para debug
		printf("[TCP] Requisição recebida:\n%s\n", buffer);

		char method_str[16] = {0};
		char path_str[256] = {0};
		char protocol_str[16] = {0};

		if (sscanf(buffer, "%15s %255s %15s", method_str, path_str, protocol_str) != 3) {
            printf("[TCP_ERROR] Requisição HTTP malformada.\n");
            const char *bad_request = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
            int len = strlen(bad_request);
            utils_send_all(client_socket, (char *)bad_request, &len); // Usando a nossa função segura!
            close(client_socket);
            continue;
        }

		int metodo = identify_method(method_str);

		char *body_ptr = NULL;
		int content_length = 0;
		int body_bytes_recebidos = 0;

		char *header_end = strstr(buffer, "\r\n\r\n");
		if (header_end) {
			body_ptr = header_end + 4;
			int bytes_dos_cabecalhos = body_ptr - buffer;
			body_bytes_recebidos = bytes_recebidos - bytes_dos_cabecalhos;

			char *cl_str = strstr(buffer, "Content-Length:");
			if (cl_str) {
				sscanf(cl_str, "Content-Length: %d", &content_length);
			}
		}

		char json_body[8192] = {0};
		if (metodo == POST || metodo == PUT) {
			if (content_length > 0 && content_length < sizeof(json_body)) {
				if (body_bytes_recebidos > 0) {
					memcpy(json_body, body_ptr, body_bytes_recebidos);
				}

				// Loop para ler o restante, se faltar
				int bytes_em_falta = content_length - body_bytes_recebidos;
				int offset = body_bytes_recebidos;

				while (bytes_em_falta > 0) {
					int n = recv(client_socket, json_body + offset,
								 bytes_em_falta, 0);
					if (n <= 0) {
						perror("[TCP_ERROR] Falha ao ler restante do body");
						break;
					}
					offset += n;
					bytes_em_falta -= n;
				}

				// Garantir terminação da string para debug
				json_body[content_length] = '\0';

				printf("[TCP] POST Recebido. Body completo:\n%s\n", json_body);

				const char *res =
					"HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n";
				int len_res = strlen(res);
				utils_send_all(client_socket, (char *)res, &len_res);
				close(client_socket);
				continue;

			} else if (content_length >= sizeof(json_body)) {
				printf("[TCP_ERROR] Payload muito grande!\n");
				const char *res = "HTTP/1.1 413 Payload Too Large\r\n\r\n";
				int len_res = strlen(res);
				utils_send_all(client_socket, (char *)res, &len_res);
				close(client_socket);
				continue;
			}
		}

		if (metodo == UNKNOWN) {
			const char *bad_request =
				"HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n"
				"<html><body><h1>400 Bad Request</h1></body></html>";
			int len = strlen(bad_request);
			utils_send_all(client_socket, (char *)bad_request, &len);
			close(client_socket);
			continue;
		}

		if (strstr(path_str, "..") != NULL) {
			printf("[SECURITY] Tentativa de Path Traversal bloqueada: %s\n",
				   path_str);
			const char *forbidden =
				"HTTP/1.1 403 Forbidden\r\n\r\n403 Acesso Negado.";
			int len = strlen(forbidden);
			utils_send_all(client_socket, (char *)forbidden, &len);
			close(client_socket);
			continue;
		}

		char filepath[SIZE_FILEPATH];
		const char *base_dir = BASE_DIR;

		if (strcmp(path_str, "/") == 0) {
			snprintf(filepath, sizeof(filepath), "%sindex.html", base_dir);
		} else {
			snprintf(filepath, sizeof(filepath), "%s%s", base_dir,
					 path_str + 1);
		}

		// Tenta abrir o arquivo index.html
		FILE *file = fopen(filepath, "r");

		if (file) {
			// Obtém tamanho do arquivo para criar cabeçalho HTTP adequado
			fseek(file, 0, SEEK_END);
			long file_size = ftell(file);
			rewind(file);

			char header[512];
			snprintf(header, sizeof(header),
					 "HTTP/1.1 200 OK\r\n"
					 "Content-Type: text/html; charset=utf-8\r\n"
					 "Content-Length: %ld\r\n"
					 "Server: C-Server-Plan9\r\n"
					 "Connection: close\r\n"
					 "\r\n",
					 file_size);

			send(client_socket, header, strlen(header), 0);

			// Envia conteúdo do arquivo em blocos
			char content[BUFFER_SIZE];
			int bytes_lidos;
			while ((bytes_lidos = fread(content, 1, BUFFER_SIZE, file)) > 0) {
				int bytes_para_enviar = bytes_lidos;

				if (utils_send_all(client_socket, content, &bytes_para_enviar) <
					0) {
					perror("[TCP_ERROR] Falha ao enviar dados do arquivo");
					break;
				}
			}

			fclose(file);
		} else {
			printf("[TCP] Arquivo nao encontrado. Retornando 404.\n");
			FILE *error_file = fopen("../../assets/html/erro.html", "r");

			const char *not_found =
				"HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
			int len = strlen(not_found);
			utils_send_all(client_socket, (char *)not_found, &len);

			if (error_file) {

				char content[BUFFER_SIZE];
				int bytes_lidos;
				while ((bytes_lidos =
							fread(content, 1, BUFFER_SIZE, error_file)) > 0) {
					int bytes_para_enviar = bytes_lidos;
					if (utils_send_all(client_socket, content,
									   &bytes_para_enviar) < 0) {
						perror("[TCP_ERROR] Falha ao enviar dados do arquivo "
							   "de erro");
						break;
					}
				}
				fclose(error_file);
			}
		}

		// Fecha conexão com cliente
		close(client_socket);
	}
}

/* --- LÓGICA RAW --- */

int net_raw_run() {
	int raw_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (raw_fd == -1) {
		if (errno == EPERM)
			fprintf(stderr, "[RAW_ERROR] Rode como SUDO!\n");
		return -1;
	}

	printf("[RAW] Raw Sniffer rodando...\n");
	unsigned char buffer[ETH_FRAME_LEN];

	while (1) {
		ssize_t bytes = recv(raw_fd, buffer, sizeof(buffer), 0);
		if (bytes < 0)
			continue;

		struct ethhdr *eth = (struct ethhdr *)buffer;
		if (ntohs(eth->h_proto) == ETH_P_ARP) {
			printf("[ARP] Capturado: %02X:%02X:%02X -> %02X:%02X:%02X\n",
				   eth->h_source[0], eth->h_source[1], eth->h_source[2],
				   eth->h_dest[0], eth->h_dest[1], eth->h_dest[2]);
		}
	}
	return 0;
}
