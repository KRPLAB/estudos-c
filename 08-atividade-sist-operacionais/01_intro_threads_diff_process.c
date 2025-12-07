/**
 * Exemplo referente as duas primeiras video-aulas da playlist "Unix Threads in C"
 * de CodeVault. URL=https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=hQPINLcOc9xeDE2R
 * É apresentada a implementação de threads e explicada a diferença de thread e processo, esclarecendo que 
 * ao chamar funcao getpid() o retorno é o mesmo, por serem threads de processamento dentro do mesmo processo
 * e por consequência compartilham os mesmos recursos e variáveis
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void* routine() {
    x += 5;
    sleep(3);
    printf("Ending thread with Process ID: %d\n", getpid());
    printf("Value of x: %d\n", x);
    return NULL;
}

void* routine2() {
    sleep(3);
    printf("Ending thread with Process ID: %d\n", getpid());
    printf("Value of x: %d\n", x);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, &routine, NULL))
        return 1;

    if (pthread_create(&t2, NULL, &routine2, NULL))
        return 1;
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}