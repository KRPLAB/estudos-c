#ifndef NETWORK_H
#define NETWORK_H

#include <linux/if_ether.h>
#include <netinet/in.h>

#define BUFFER_SIZE 4096
#define PORT 8080
#define BASE_DIR "../../assets/html/"
#define SIZE_FILEPATH 512

typedef struct {
    int server_socket;
    int port;
    int running;
} net_ctx_t;

/**
 * @brief Configura o socket TCP (Socket, Setsockopt, Bind, Listen).
 * @param ctx Contexto da rede, onde o socket e porta serão armazenados.
 * @param port Porta na qual o servidor TCP irá escutar.
 * @return 0 em caso de sucesso, -1 em caso de erro.
 */
int net_tcp_setup(net_ctx_t *ctx, int port);

/**
 * @brief Bloqueia a execução no loop de aceitação TCP.
 * @param ctx Contexto da rede, contendo o socket e estado de execução.
 * @param client_socket Socket do cliente, preenchido após a aceitação.
 * @param client_addr Estrutura para armazenar o endereço do cliente (preparada para o accept).
 * @param client_len Tamanho da estrutura de endereço do cliente.
 * @param buffer Buffer para armazenar os dados recebidos.
 */
void net_tcp_run(net_ctx_t *ctx, int client_socket, struct sockaddr_in client_addr, socklen_t client_len, char *buffer);

/**
 * @brief Cria o Raw Socket e já entra no loop de captura (Sniffer).
 * @return 0 em caso de sucesso, -1 em caso de erro.
 */
int net_raw_run(); 

#endif
