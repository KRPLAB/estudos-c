/* hello.c - Nosso primeiro programa para AArch64 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Olá do mundo ARM64! Meu PID é %d.\n", getpid());
    return 0;
}