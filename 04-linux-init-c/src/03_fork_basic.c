/* fork_demo.c - Demonstra a criação de um processo filho. */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    int retval;

    printf("Início do programa. Meu PID é %d\n", getpid());

    retval = fork(); // O processo é clonado aqui!

    if (retval < 0) {
        perror("fork falhou");
        exit(1);
    } else if (retval == 0) {
        // Bloco de código do processo FILHO
        printf("--> [FILHO] Olá! Meu PID é %d.\n", getpid());
        printf("--> [FILHO] Meu pai tem o PID %d.\n", getppid());
    } else {
        // Bloco de código do processo PAI
        printf("--> [PAI] Eu criei um filho com PID = %d\n", retval);
        printf("--> [PAI] Meu PID continua sendo %d.\n", getpid());
    }

    printf("Fim do escopo do main para o processo PID=%d\n", getpid());
    return 0;
}

