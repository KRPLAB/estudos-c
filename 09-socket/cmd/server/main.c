#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/common.h"

int main() {
    // Porta padrão para o servidor HTTP. Se for raw socket pode comentar essa linha
    // int port = 8080;
    // printf("[MAIN] Iniciando o servidor na porta %d...\n", port);

    printf("[MAIN] Iniciando o servidor raw socket...\n");

    // int server_fd = net_server_start(port);
    int server_fd = net_raw_socket_start();

    if (server_fd == -1) {
        exit(EXIT_FAILURE);
    }

    close(server_fd);
    printf("[MAIN] Servidor encerrado.\n");

    return 0;
}
