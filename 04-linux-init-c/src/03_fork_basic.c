#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	    pid_t pid_fork;

	        printf("--- Início do Programa ---\n");
		    printf("Meu PID antes do fork é: %d\n", getpid());
		        printf("Vou criar um novo processo agora...\n\n");

			    pid_fork = fork();

			        if (pid_fork < 0) {
					        // --- Tratamento de Erro ---
						//         fprintf(stderr, "A criação do processo filho falhou!\n");
						//                 return 1;
						//                     } else if (pid_fork == 0) {
						//                             // --- Bloco de código do FILHO ---
						//                                     printf("[FILHO] 👶 Meu PID é: %d\n", getpid());
						//                                             printf("[FILHO] 👶 O PID do meu pai é: %d\n", getppid());
						//                                                 } else {
						//                                                         // --- Bloco de código do PAI ---
						//                                                                 printf("[PAI] 👴 Meu PID é: %d\n", getpid());
						//                                                                         printf("[PAI] 👴 O PID do meu processo filho é: %d\n", pid_fork);
						//                                                                                 printf("[PAI] 👴 O PID do meu pai (o shell) é: %d\n", getppid());
						//                                                                                     }
						//
						//                                                                                         // Esta linha será executada por AMBOS os processos!
						//                                                                                             printf("--- Fim da execução para o processo %d ---\n", getpid());
						//
						//                                                                                                 return 0;
						//                                                                                                 }
						//
