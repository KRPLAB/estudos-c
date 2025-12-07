#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

#define NUM_THREADS 1
#define NUM_ITERACOES 1000000000
#define PASSO (NUM_ITERACOES / NUM_THREADS)

double resultado_parcial[NUM_THREADS] = {0};

void *threadBody(void *id) {
    long tid = (long)(intptr_t)id;

    // Cálculo dinâmico do intervalo (Decomposição de Domínio)
    // Isso cumpre o requisito: "Divida o cálculo igualmente" [cite: 22]
    long termos_por_thread = NUM_ITERACOES / NUM_THREADS;

    double inicio = termos_por_thread * tid;
    double fim = inicio + termos_por_thread - 1;

    // Ajuste para a última thread pegar qualquer sobra (caso a divisão não seja exata)
    if (tid == NUM_THREADS - 1) {
        fim = NUM_ITERACOES - 1;
    }

    double soma = 0.0;
    double sinal = (((long)inicio % 2) == 0) ? 1.0 : -1.0;

    for (long i = inicio; i <= fim; i++) {
        soma += sinal / (2.0 * i + 1.0);
        sinal = -sinal;
    }

    resultado_parcial[tid] = soma;

    printf("t%02ld: Soma de %.0f a %.0f é %.15f\n", tid, inicio, fim, soma);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int i, status;
    double soma_total = 0.0;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("Iniciando cálculo com %d threads...\n", NUM_THREADS);

    for (i = 0; i < NUM_THREADS; i++) {
        status = pthread_create(&thread[i], &attr, threadBody, (void *)(intptr_t)i);
        if (status) {
            perror("pthread_create");
            exit(1);
        }
    }


    for (i = 0; i < NUM_THREADS; i++) {
        status = pthread_join(thread[i], NULL);
        if (status) {
            perror("pthread_join");
            exit(1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        soma_total += resultado_parcial[i];
    }

    double pi_final = soma_total * 4.0;

    printf("\nValor estimado de PI: %.15f\n", pi_final);
    printf("Valor real de PI:     3.141592653589793 (ref: https://pt.wikipedia.org/wiki/Pi)\n");

    printf("Main: fim\n");

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}