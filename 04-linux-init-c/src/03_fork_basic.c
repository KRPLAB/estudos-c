/* fork_demo.c - Demonstra a criação de um processo filho. */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid_filho;

    printf("Início do programa. Meu PID é %d\n", getpid());

    pid_filho = fork(); // O processo é clonado aqui!

    if (pid_filho < 0) {
        perror("fork falhou");
        return 1;
    } else if (pid_filho == 0) {
        // Bloco de código do processo FILHO
        printf("--> [FILHO] Olá! Meu PID é %d.\n", getpid());
        printf("--> [FILHO] Meu pai tem o PID %d.\n", getppid());
    } else {
        // Bloco de código do processo PAI
        printf("--> [PAI] Eu criei um filho com PID = %d\n", pid_filho);
        printf("--> [PAI] Meu PID continua sendo %d.\n", getpid());
    }

    printf("Fim do escopo do main para o processo PID=%d\n", getpid());
    return 0;
}

