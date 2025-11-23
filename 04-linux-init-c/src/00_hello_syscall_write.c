//Invocação de uma syscall write para imprimir uma mensagem na saída padrão.
#include <unistd.h>

int main (int argc, char *argv[]) {
    write(1, "Hello, World!\n", 14);
    _exit(0);
}