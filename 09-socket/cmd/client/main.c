/**
 * @file main.c (cliente)
 * @brief Cliente HTTP - ponto de entrada
 */

#include "../../include/client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT 8080
#define DEFAULT_PATH "/"

void print_usage(const char *prog_name) {
	printf("Uso: %s [opções]\n", prog_name);
	printf("Opções:\n");
	printf("  -h <host>     IP do servidor (padrão: %s)\n", DEFAULT_HOST);
	printf("  -p <port>     Porta do servidor (padrão: %d)\n", DEFAULT_PORT);
	printf("  -r <path>     Caminho da requisição (padrão: %s)\n", DEFAULT_PATH);
	printf("  --help        Exibe esta mensagem\n");
	printf("\nExemplo:\n");
	printf("  %s -h 127.0.0.1 -p 8080 -r /\n", prog_name);
}

int main(int argc, char *argv[]) {
	client_ctx_t client;
	char host[256] = DEFAULT_HOST;
	int port = DEFAULT_PORT;
	char path[256] = DEFAULT_PATH;
	char buffer[BUFFER_SIZE];

	// Parse de argumentos
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
			strncpy(host, argv[++i], sizeof(host) - 1);
		} else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
			port = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
			strncpy(path, argv[++i], sizeof(path) - 1);
		} else if (strcmp(argv[i], "--help") == 0) {
			print_usage(argv[0]);
			return 0;
		} else {
			fprintf(stderr, "Opção desconhecida: %s\n\n", argv[i]);
			print_usage(argv[0]);
			return 1;
		}
	}

	printf("=== Cliente HTTP ===\n");
	printf("Servidor: %s:%d\n", host, port);
	printf("Caminho: %s\n\n", path);

	// Conecta ao servidor
	if (client_http_connect(&client, host, port) != 0) {
		fprintf(stderr, "[ERRO] Falha ao conectar ao servidor\n");
		return 1;
	}

	// Envia requisição GET
	if (client_http_send_get(&client, path, host) < 0) {
		fprintf(stderr, "[ERRO] Falha ao enviar requisição\n");
		close(client.socket);
		return 1;
	}

	// Recebe resposta completa (loop até fechar conexão)
	printf("\n=== Resposta do Servidor ===\n");
	int total_bytes = 0;
	while (1) {
		int bytes = recv(client.socket, buffer, BUFFER_SIZE - 1, 0);
		if (bytes <= 0) break;  // Conexão fechada ou erro
		buffer[bytes] = '\0';
		printf("%s", buffer);
		total_bytes += bytes;
	}
	printf("\n\n[CLIENT] Total recebido: %d bytes\n", total_bytes);

	// Fecha conexão
	client_http_close(&client);

	return 0;
}
