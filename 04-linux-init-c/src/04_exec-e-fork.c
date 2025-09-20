#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    printf("Início do programa. Meu PID é %d\n", getpid());

    // clonando o processo
    pid_t pid_filho = fork();

    if (pid_filho < 0)
    {
        perror("fork falhou");
        return 1;
    }
    else if (pid_filho == 0)
    {
        printf("--> [FILHO] Meu PID é %d. Vou me transformar no comando 'ls -lh'.\n", getpid());

        // Substitui este processo pelo comando 'ls'
        // Argumentos: programa, arg0, arg1, arg2, ..., NULL
        execlp("ls", "ls", "-l", "-h", NULL);

        // Esta parte do código SÓ é executada se o execlp falhar!
        perror("execlp falhou");
        return 1;
    }
    else
    {
        // --- Bloco do Pai ---
        printf("--> [PAI] Criei o filho com PID %d. Vou aguardar ele terminar.\n", pid_filho);
        // (Em uma task futura, aprenderemos a esperar de verdade com wait())
    }

    // Apenas o pai chegará aqui (se o exec do filho funcionar)
    printf("--> [PAI] O filho já deve ter terminado. Fim do programa.\n");

    return 0;
}
