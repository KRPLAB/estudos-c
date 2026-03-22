/*
 * Implementação do método da secante para encontrar raízes de funções.
 * O método da secante é um método numérico que encontra raízes de funções contínuas
 * utilizando uma aproximação linear da função. Ele é semelhante ao método de Newton, mas não requer o cálculo da derivada da função.
 * O programa define uma função f(x) e utiliza o método da secante para encontrar uma raiz dessa função a partir de duas aproximações iniciais 
 * fornecidas pelo usuário.
 */

#include <stdio.h>
#include <math.h>

// Definição da função f(x) para a qual queremos encontrar a raiz
double f(double x) {
    return x*log10(x) - 1; // Exemplo: f(x) = x * log10(x) - 1
}

// Implementação do método da secante
double secante(double x0, double x1, double tol1, double tol2, int max_iter) {
    double x_novo;

    for(int i = 0; i < max_iter; i++) {
        x_novo = ( (f(x0) * x1) - (f(x1) * x0) ) / (f(x0) - f(x1));
        if(fabs(f(x_novo)) < tol1 || fabs(x_novo - x1) < tol2 * fmax(1.0, fabs(x_novo))) {
            return x_novo;
        }
        x0 = x1;
        x1 = x_novo;
    }
    return x_novo;
}

int main() {
    double x0, x1, tol1, tol2;
    int max_iter;
    // Solicita ao usuário os valores de x0, x1, tolerâncias e número máximo de iterações
    printf("Digite o valor de x0: ");
    scanf("%lf", &x0);
    printf("Digite o valor de x1: ");
    scanf("%lf", &x1);
    printf("Digite a tolerância para f(x): ");
    scanf("%lf", &tol1);
    printf("Digite a tolerância para x: ");
    scanf("%lf", &tol2);
    printf("Digite o número máximo de iterações: ");
    scanf("%d", &max_iter);

    // Chama a função da secante para encontrar a raiz
    double raiz = secante(x0, x1, tol1, tol2, max_iter);

    printf("A raiz encontrada é: %lf\n", raiz);

    return 0;
}