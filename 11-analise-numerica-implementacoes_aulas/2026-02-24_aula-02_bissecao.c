/*
 * Implementação do método da bisseção para encontrar raízes de funções.
 * O método da bisseção é um método numérico que encontra raízes de funções contínuas
 * em um intervalo [a, b] onde a função muda de sinal (f(a) * f(b) < 0).
 *
 * O programa define uma função f(x) e utiliza o método da bisseção para encontrar uma raiz
 * dessa função dentro de um intervalo especificado pelo usuário.
 *
 * O programa também inclui uma função para calcular o valor de f(x) e uma função para realizar
 * o método da bisseção.
 */

#include <stdio.h>
#include <math.h>

// Definição da função f(x) para a qual queremos encontrar a raiz
double f(double x) {
    return x*log10(x) - 1; // Exemplo: f(x) = x * log10(x) - 1
}

// Implementação do método da bisseção
double bissecao(double *a, double *b, double tolerancia, int max_iter) {
    double x;

    for(int i = 0; i < max_iter; i++) {
        x = (*a + *b) / 2;
        if((f(*a) * f(x)) < 0)
            *b = x;
        else
            *a = x;
        if(fabs(*b - *a) < tolerancia)
            return x;
    }
    return x;
}

int main() {
    double a, b, tolerancia;
    int max_iter;

    // Solicita ao usuário os valores de a, b, tolerância e número máximo de iterações
    printf("Digite o valor de a: ");
    scanf("%lf", &a);
    printf("Digite o valor de b: ");
    scanf("%lf", &b);
    printf("Digite a tolerância: ");
    scanf("%lf", &tolerancia);
    printf("Digite o número máximo de iterações: ");
    scanf("%d", &max_iter);

    // Verifica se f(a) e f(b) têm sinais opostos
    if(f(a) * f(b) >= 0) {
        printf("f(a) e f(b) devem ter sinais opostos. Por favor, escolha um intervalo válido.\n");
        return 1;
    }

    // Chama a função da bisseção para encontrar a raiz
    double raiz = bissecao(&a, &b, tolerancia, max_iter);
    printf("A raiz encontrada é: %lf\n", raiz);

    return 0;
}