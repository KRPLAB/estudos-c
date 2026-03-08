#include "../../include/common.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

int create_server_socket(uint16_t port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        log_msg("Erro ao criar socket");
        return -1;
    }
    
    // Configura SO_REUSEADDR (Permite reusar a porta imediatamente após matar o processo)
    int val = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        log_msg("Erro: setsockopt()");
        close(fd);
        return -1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Aceita conexões em qualquer interface
    addr.sin_port = htons(port); // Beej's Guide: Converter para network byte order
    
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        log_msg("Erro: bind() - Porta em uso?");
        close(fd);
        return -1;
    }

    // SOMAXCONN é o backlog padrão do sistema (geralmente 128 ou 4096)
    if (listen(fd, SOMAXCONN) < 0) {
        log_msg("Erro: listen()");
        close(fd);
        return -1;
    }

    return fd;
}
