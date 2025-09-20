/* pid_info.c - Explora a identidade de um processo. */
#include <stdio.h>
#include <unistd.h>    // Para getpid() e getppid()
#include <sys/types.h> // Para o tipo pid_t

int main(void)
{
    pid_t meu_pid;
    pid_t meu_ppid;

    meu_pid = getpid();
    meu_ppid = getppid();

    printf("Eu sou o processo com PID = %d\n", meu_pid);
    printf("Meu processo pai tem o PID = %d\n", meu_ppid);

    return 0;
}