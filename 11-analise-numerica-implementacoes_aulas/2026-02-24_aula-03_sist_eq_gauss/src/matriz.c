#include <stdio.h>

#include "matriz.h"

void leitura_matriz(double **m, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%lf", &m[i][j]);
        }
    }
}

void impressao_matriz(double **m, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%8.2lf ", m[i][j]);
        }
        printf("\n");
    }
}

int troca_linha(double **m, int linha1, int linha2, int linhas, int colunas) {
    if (linha1 >= linhas || linha2 >= linhas || linha1 < 0 || linha2 < 0) {
        return -1;
    }

    double *temp = m[linha1];
    m[linha1] = m[linha2];
    m[linha2] = temp;
    return 1;
}