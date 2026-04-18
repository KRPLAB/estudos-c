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

	// Cria socket TCP IPv4
	ctx->socket = socket(AF_INET, SOCK_STREAM, 0);

	if (ctx->socket < 0) {
		perror("[CLIENT_ERROR] Falha ao criar socket");
		return -1;
	}

	// Configura endereço do servidor
	ctx->server.sin_family = AF_INET;
	ctx->server.sin_port = htons(port);

	// Converte o host (IP) para formato binário
	if (inet_pton(AF_INET, host, &ctx->server.sin_addr) <= 0) {
		perror("[CLIENT_ERROR] Endereço IP inválido");
		close(ctx->socket);
		return -1;
	}

	// Conecta ao servidor
	if (connect(ctx->socket, (struct sockaddr *)&ctx->server, sizeof(ctx->server)) < 0) {
		perror("[CLIENT_ERROR] Falha ao conectar ao servidor");
		close(ctx->socket);
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
	snprintf(request, sizeof(request),
			 "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
			 path, host);

	// Envia requisição
	int bytes_sent = send(ctx->socket, request, strlen(request), 0);

	if (bytes_sent < 0) {
		perror("[CLIENT_ERROR] Falha ao enviar requisição");
		return -1;
	}

	printf("[CLIENT] Requisição enviada (%d bytes)\n", bytes_sent);
	return bytes_sent;
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
