#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define NUM_THREADS 4
#define PASSO 25

int intervalo[NUM_THREADS] = {1, 26, 51, 76};
int resultado_parcial[NUM_THREADS] = {0, 0, 0, 0};

void *threadBody(void *id) {
    int tid = (int)(intptr_t)id;

    int inicio = intervalo[tid];
    int fim = inicio + PASSO - 1;
    int soma = 0;

    for (int i = inicio; i <= fim; i++) {
        soma += i;
    }
    resultado_parcial[tid] = soma;
    sleep(3);
    printf("t%02d: Soma de %d a %d é %d\n", tid, inicio, fim, soma);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int i, status;
    int soma_total = 0;

    // para permitir a operação "join" sobre as threads
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < NUM_THREADS; i++) {
        printf("Main: criando thread %02d\n", i);
        status = pthread_create(&thread[i], &attr, threadBody, (void *)(intptr_t)i);
        if (status) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        printf("Main: aguardando thread %02d\n", i);
        status = pthread_join(thread[i], NULL);
        if (status) {
            perror("pthread_join");
            exit(1);
        }
    }
    for (i = 0; i < NUM_THREADS; i++) {
        soma_total += resultado_parcial[i];
    }
    printf("Soma total de 1 a 100 é %d\n", soma_total);
    printf("Main: fim\n");
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}