/**
 * @file client.h
 * @brief Interface de cliente HTTP para comunicação com servidor TCP
 * @author Kauan da Rosa Paulino
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>

/**
 * @brief Contexto de cliente HTTP
 */
typedef struct {
    int socket;                  // Socket do cliente
    struct sockaddr_in server;   // Estrutura com endereço do servidor
} client_ctx_t;

/**
 * @brief Conecta ao servidor HTTP
 * @param ctx Contexto do cliente a ser preenchido
 * @param host IP ou hostname do servidor
 * @param port Porta do servidor
 * @return 0 em sucesso, -1 em erro
 */
int client_http_connect(client_ctx_t *ctx, const char *host, int port);

/**
 * @brief Envia requisição HTTP GET simples
 * @param ctx Contexto do cliente conectado
 * @param path Caminho da requisição (ex: "/")
 * @param host Host header HTTP
 * @return Número de bytes enviados, -1 em erro
 */
int client_http_send_get(client_ctx_t *ctx, const char *path, const char *host);

/**
 * @brief Recebe resposta HTTP do servidor
 * @param ctx Contexto do cliente conectado
 * @param buffer Buffer para armazenar resposta
 * @param buffer_size Tamanho do buffer
 * @return Número de bytes recebidos, -1 em erro
 */
int client_http_recv(client_ctx_t *ctx, char *buffer, int buffer_size);

/**
 * @brief Fecha conexão com servidor
 * @param ctx Contexto do cliente
 * @return 0 em sucesso
 */
int client_http_close(client_ctx_t *ctx);

#endif
