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

enum method {
    GET,
    POST,
    PUT,
    PATCH,
    DELETE,
    UNKNOWN
};

#endif
