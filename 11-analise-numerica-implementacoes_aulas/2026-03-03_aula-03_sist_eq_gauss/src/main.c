#include <stdlib.h>
#include <stdio.h>
#include <matriz.h>
#include <triangulacao_gauss.h>

int main() {
    int linhas, colunas;
    double **matriz;
    double *x;
    PassoTriangulacao passos[100]; 
    int num_passos, trocas;

    printf("Digite o número de x's e o número de equações (linhas e colunas da matriz): ");
    
    scanf("%d %d", &linhas, &colunas);
    if(linhas <= 0 || colunas <= 0) {
        printf("Número de linhas e colunas deve ser positivo.\n");
        return 1;
    }

    if(colunas != linhas + 1) {
        printf("Número de colunas deve ser igual ao número de linhas + 1 (matriz aumentada).\n");
        return 1;
    }

    // Alocação dinâmica da matriz
    if((matriz = malloc(linhas * sizeof(double*))) == NULL) {
        printf("Erro de alocação de memória para matriz.\n");
        return 1;
    }

    for (int i = 0; i < linhas; i++) {
        if((matriz[i] = malloc(colunas * sizeof(double))) == NULL) {
            printf("Erro de alocação de memória para matriz[%d].\n", i);
            return 1;
        }
    }

    // Alocação dinâmica do vetor solução
    if((x = malloc(linhas * sizeof(double))) == NULL) {
        printf("Erro de alocação de memória para vetor solução.\n");
        return 1;
    }

    printf("Digite os elementos da matriz aumentada (coeficientes e termos independentes):\n");
    leitura_matriz(matriz, linhas, colunas);

    printf("Matriz aumentada antes da triangulação:\n");
    impressao_matriz(matriz, linhas, colunas);

    if (triangular_matriz(matriz, passos, &num_passos, &trocas, linhas, colunas) == -1) {
        printf("A matriz é singular ou quase singular. Não é possível triangularizar.\n");
        return 1;
    }

    printf("Matriz aumentada após a triangulação:\n");
    impressao_matriz(matriz, linhas, colunas);

    valores_x_retrosubstituicao(matriz, x, linhas, colunas);

    printf("Solução do sistema:\n");
    for (int i = 0; i < linhas; i++) {
        printf("x[%d] = %lf\n", i, x[i]);
    }

    // Liberação da memória alocada
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    free(x);
    return 0;
}
