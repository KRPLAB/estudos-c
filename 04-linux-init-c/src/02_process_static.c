#include <stdio.h>

#include <unistd.h>

#define MAX_PATH_LEN 256

int main()
{
    // 1. Variável para guardar o PID.
    //    'pid_t' é um tipo de dado especial para Process IDs, definido em unistd.h.

    pid_t meu_pid;

    // 2. Buffer (espaço na memória) para guardar a string do diretório atual.
    char diretorio_atual[MAX_PATH_LEN];

    meu_pid = getpid();

    if (!getcwd(diretorio_atual, MAX_PATH_LEN))
        return -1;

    printf("--- Informações do Processo ---\n");

    printf("Meu Process ID (PID) é: %d\n", meu_pid);

    printf("Estou no diretório: %s\n", diretorio_atual);

    return 0;
}
