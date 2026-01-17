#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Erro ao criar o pipe\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if(write(fd[1], &x, sizeof(int)) == -1) {
            perror("Erro ao escrever no pipe\n");
            return 1;
        }
        close(fd[1]);
    }
    else {
        close(fd[1]);
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1) {
            perror("Erro ao ler do pipe\n");
            return 1;
        }
        close(fd[0]);
        printf("Received number from child: %d\n", y);
        wait(NULL);
    }

    return 0;
}
