/**
 * @file common.h
 * @brief Declarações de funções comuns de rede.
 * 
 * Este arquivo contém protótipos para funções de rede compartilhadas,
 * como inicialização de servidores e sockets raw.
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Inicializa e inicia um servidor TCP em uma porta específica.
 * 
 * Cria um socket, faz o bind para o endereço e porta especificados,
 * e começa a escutar por conexões entrantes.
 * 
 * @param port Um valor inteiro representando a porta na qual o servidor irá escutar.
 * @return O file descriptor do socket do servidor em caso de sucesso.
 * @return -1 em caso de erro.
 */
int net_server_start(int port);

/**
 * @brief Cria e inicializa um raw socket.
 * 
 * Esta função cria um endpoint para comunicação usando um raw socket,
 * permitindo o envio e recebimento de pacotes de rede brutos.
 * 
 * @return O file descriptor do raw socket em caso de sucesso.
 * @return -1 em caso de erro.
 */
int net_raw_socket_start();
#endif
