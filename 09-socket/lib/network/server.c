#include <stdio.h>
#include <unistd.h>                 // p/ a função close()
#include <sys/socket.h>             // p/ socket(), bind(), listen()
#include <arpa/inet.h>              // p/ as estruturas sockaddr_in
#include <errno.h>                  // p/ capturar erros
#include <string.h>                 // p/ strerror()
#include <linux/if_ether.h>         // p/ ETH_P_ALL
#include "../../include/common.h"


int net_server_start(int port) {
    int server_fd;

    // 1. Criando o Socket
    // AF_INET = IPv4 | SOCK_STREAM = TCP | 0 = Protocolo Padrão (IPPROTO_TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_fd == -1) {
        fprintf(stderr, "[ERRO FATAL] Falha ao criar o socket: %s\n", strerror(errno));
        return -1;
    }

    printf("[INFO] Socket criado com sucesso! File Descriptor: %d\n", server_fd);

    // TODO: Adicionar setsockopt() p/ reuso de porta
    

    // TODO: Adicionar bind()
    // TODO: Adicionar listen()

    return server_fd;
}

int net_raw_socket_start() {
    int raw_fd;

    // 1. Criando o Raw Socket Spoof (Nível de Enlace)
    // AF_PACKET = Intercepta os quadros Ethernet | SOCK_RAW = Entrega o quadro completo (incluindo cabeçalho MAC) | htons(ETH_P_ALL) = Captura todos os protocolos (IPv4, ARP, IPv6) de 2 bytes
    raw_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    
    if (raw_fd == -1) {
        fprintf(stderr, "[ERRO FATAL] Falha ao criar Raw Socket: %s\n", strerror(errno));
        if (errno == EPERM) {
            fprintf(stderr, "-> VOCÊ ESQUECEU DE RODAR COM SUDO?\n");
        }
        return -1;
    }

    printf("[INFO] Raw Socket criado com sucesso! File Descriptor: %d\n", raw_fd);
    printf("[INFO] Atualmente na Camada de Enlace.\n");

    // ETH_FRAME_LEN é 1514 bytes (MTU 1500 + 14 Header).
    unsigned char buffer[ETH_FRAME_LEN]; 

    while(1) {
        // Recebe um quadro Ethernet (incluindo o cabeçalho MAC) e armazena no buffer. O número de bytes recebidos é retornado.
        ssize_t num_bytes = recv(raw_fd, buffer, sizeof(buffer), 0);
        
        if (num_bytes == -1) {
            fprintf(stderr, "[ERRO] Falha ao receber pacote: %s\n", strerror(errno));
            continue; 
        }

        // Converte o buffer recebido para a estrutura de cabeçalho Ethernet
        // Consultar struct para ver os campos
        struct ethhdr *eth = (struct ethhdr *)buffer;
        
        // Verifica se o protocolo é ARP (0x0806). Se for, imprime as informações do quadro ARP.
        // Outras opções de protocolo poderiam ser adicionadas aqui (IPv4 = 0x0800 = ETH_P_IP, IPv6 = 0x86DD = , etc).
        // ntohs() é usado para converter o valor do campo h_proto de network byte order (big-endian) para host byte order (pode ser little-endian dependendo da arquitetura).
        if (ntohs(eth->h_proto) == ETH_P_ARP) {
            printf("\n[+] Novo Quadro ARP Capturado! (%zd bytes)\n", num_bytes);
        
            printf("    MAC Destino: %02X:%02X:%02X:%02X:%02X:%02X\n",
                eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], 
                eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);

            printf("    MAC Origem:  %02X:%02X:%02X:%02X:%02X:%02X\n",
                eth->h_source[0], eth->h_source[1], eth->h_source[2], 
                eth->h_source[3], eth->h_source[4], eth->h_source[5]);
        }
    }

    return raw_fd;
}
