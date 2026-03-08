#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>

// Logging (Task 01)
void log_msg(const char *msg);

// Network (Task 02)
// Retorna o file descriptor do socket ouvindo, ou -1 em erro
int create_server_socket(uint16_t port);
#endif // COMMON_H