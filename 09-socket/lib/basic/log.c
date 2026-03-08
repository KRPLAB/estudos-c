#include "../../include/common.h"
#include <unistd.h>
#include <string.h>

void log_msg(const char *msg) {
    // Função simples de logging que imprime a mensagem no console
    write(1, "\n", 1);
    write(1, msg, strlen(msg));
    write(1, "\n", 1);
}