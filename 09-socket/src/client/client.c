/**
 * @file client.c
 * @brief Implementação de cliente HTTP para comunicação com servidor TCP
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../include/client.h"

int client_http_connect(client_ctx_t *ctx, const char *host, int port) {
	if (!ctx || !host) {
		fprintf(stderr, "[CLIENT_ERROR] Parâmetros inválidos\n");
		return -1;
	}

	if (port <= 0 || port > 65535) {
		fprintf(stderr, "[CLIENT_ERROR] Porta inválida: %d\n", port);
		return -1;
	}

	// garante estado limpo
	memset(&ctx->server, 0, sizeof(ctx->server));
	ctx->socket = -1;

	// configura família e porta PRIMEIRO
	ctx->server.sin_family = AF_INET;
	ctx->server.sin_port = htons(port);

	// converte IP (apenas IPv4)
	int ret = inet_pton(AF_INET, host, &ctx->server.sin_addr);

	if (ret == 0) {
		fprintf(stderr, "[CLIENT_ERROR] IP inválido: %s\n", host);
		return -1;
	}

	if (ret < 0) {
		perror("[CLIENT_ERROR] inet_pton falhou");
		return -1;
	}

	// cria socket TCP
	ctx->socket = socket(AF_INET, SOCK_STREAM, 0);

	if (ctx->socket < 0) {
		perror("[CLIENT_ERROR] Falha ao criar socket");
		return -1;
	}

	// conecta ao servidor (dispara handshake TCP)
	if (connect(ctx->socket,
				(struct sockaddr *)&ctx->server,
				sizeof(ctx->server)) < 0) {
		perror("[CLIENT_ERROR] Falha ao conectar ao servidor");
		close(ctx->socket);
		ctx->socket = -1;
		return -1;
	}

	printf("[CLIENT] Conectado ao servidor %s:%d\n", host, port);
	return 0;
}

int client_http_send_get(client_ctx_t *ctx, const char *path, const char *host) {
	if (!ctx || !path || !host) {
		fprintf(stderr, "[CLIENT_ERROR] Parâmetros inválidos\n");
		return -1;
	}

	// Monta requisição HTTP GET
	char request[512];
	int request_len = snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
             path, host);

	// Envia requisição
    int total_sent = 0;

    while (total_sent < request_len) {
        int bytes_sent = send(ctx->socket, request + total_sent, request_len - total_sent, 0);

        if (bytes_sent == -1) {
            perror("[CLIENT ERROR] Falha ao enviar dados");
            close(ctx->socket);
            return -1;
        }

        total_sent += bytes_sent;
        printf("[CLIENT] Enviados %d bytes... Total: %d/%d\n", bytes_sent, total_sent, request_len);
    }

    return total_sent;
}

int client_http_recv(client_ctx_t *ctx, char *buffer, int buffer_size) {
	if (!ctx || !buffer || buffer_size <= 0) {
		fprintf(stderr, "[CLIENT_ERROR] Parâmetros inválidos\n");
		return -1;
	}

	// Recebe dados do servidor
	int bytes_recv = recv(ctx->socket, buffer, buffer_size - 1, 0);

	if (bytes_recv < 0) {
		perror("[CLIENT_ERROR] Falha ao receber dados");
		return -1;
	}

	// Adiciona terminador de string
	buffer[bytes_recv] = '\0';

	printf("[CLIENT] Resposta recebida (%d bytes)\n", bytes_recv);
	return bytes_recv;
}

int client_http_close(client_ctx_t *ctx) {
	if (!ctx || ctx->socket < 0) {
		fprintf(stderr, "[CLIENT_ERROR] Socket inválido\n");
		return -1;
	}

	close(ctx->socket);
	printf("[CLIENT] Conexão fechada\n");
	return 0;
}
