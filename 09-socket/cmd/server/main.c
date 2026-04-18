#include "../../include/network.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s [tcp|raw]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "tcp") == 0) {
        net_ctx_t server;
        int client_socket = 0;
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        char buffer[BUFFER_SIZE];
        int port;
        
        printf("Porta atual: %d\n", PORT);
        printf("Deseja alterar a porta? (s/n): ");
        char choice = getchar();
        if (choice == 's' || choice == 'S') {
            printf("Digite a nova porta: ");
            if (scanf("%d", &port) != 1) {
                fprintf(stderr, "[ERRO] Entrada inválida para porta\n");
                fprintf(stdout, "Usando porta padrão.\n");
                port = PORT;
            }
        } else {
            port = PORT;
        }

        if (net_tcp_setup(&server, port) == 0) {
            net_tcp_run(&server, client_socket, client_addr, client_len, buffer);
            close(server.server_socket);
        }
    } 
    else if (strcmp(argv[1], "raw") == 0) {
        if (net_raw_run() == -1) return 1;
    } 
    else {
        printf("Opção inválida.\n");
        return 1;
    }

    return 0;
}

