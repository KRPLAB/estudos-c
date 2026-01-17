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
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "/usr", NULL);
    }
    else {
        close(fd[1]);
        char buffer[1024];
        ssize_t nbytes;
        while ((nbytes = read(fd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[nbytes] = '\0';
            printf("%s", buffer);
        }

        close(fd[0]);
        wait(NULL);
    }

    return 0;
}