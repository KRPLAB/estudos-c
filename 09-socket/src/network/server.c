// bibliotecas padrão
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
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

		// Identifica método da requisição
		char *first_line = tokenize(buffer, "\r\n");
		int metodo = identify_method(first_line);

		if (metodo == UNKNOWN) {
			const char *bad_request =
				"HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n"
				"<html><body><h1>400 Bad Request</h1></body></html>";
			send(client_socket, bad_request, strlen(bad_request), 0);
			close(client_socket);
			continue;
		}

		// Tenta abrir o arquivo index.html
		FILE *file = fopen("../../assets/html/index.html", "r");

		if (file) {
			// Envia cabeçalho HTTP 200 OK
			const char *header =
				"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
			send(client_socket, header, strlen(header), 0);

			// Envia conteúdo do arquivo em blocos
			char content[BUFFER_SIZE];
			int bytes;
			while ((bytes = fread(content, 1, BUFFER_SIZE, file)) > 0) {
				send(client_socket, content, bytes, 0);
			}

			fclose(file);
		} else {
			// Se não achar index.html, envia erro 404
			FILE *error_file = fopen("../../assets/html/erro.html", "r");

			const char *not_found =
				"HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
			send(client_socket, not_found, strlen(not_found), 0);

			if (error_file) {
				char content[BUFFER_SIZE];
				int bytes;
				while ((bytes = fread(content, 1, BUFFER_SIZE, error_file)) >
					   0) {
					send(client_socket, content, bytes, 0);
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
