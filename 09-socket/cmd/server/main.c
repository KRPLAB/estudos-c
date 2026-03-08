#include "../../include/common.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
    log_msg("Redis Init: Starting Server on port 6379...");

    int server_fd = create_server_socket(6379);
    if (server_fd < 0) {
        return 1;
    }
    
    log_msg("Waiting for connections...");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        
        // accept bloqueia até alguém conectar
        int conn_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        
        if (conn_fd < 0) {
            log_msg("Erro no accept (ignorando)");
            continue; // Em servidor real, não paramos por um erro de conexão
        }

        log_msg("Client connected!");
        
        // Por enquanto, apenas fechamos para evitar vazamento de fd
        close(conn_fd); 
    }

    close(server_fd);
    return 0;
}