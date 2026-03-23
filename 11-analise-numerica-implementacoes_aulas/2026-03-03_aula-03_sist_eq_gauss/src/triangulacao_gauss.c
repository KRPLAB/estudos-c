#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "triangulacao_gauss.h"
#include "matriz.h"

void atualiza_passo_triangulacao(PassoTriangulacao *passo, int passo_num, int linha_pivo, int coluna_pivo, double valor_pivo) {
    passo->passo = passo_num;
    passo->linha_pivo = linha_pivo;
    passo->coluna_pivo = coluna_pivo;
    passo->valor_pivo = valor_pivo;
}

int triangular_matriz(double **matriz, PassoTriangulacao passos[], int *num_passos, int *trocas, int linhas, int colunas) {
    *num_passos = 0;

    // 1. LOOP DO PIVÔ (p): Percorre a diagonal principal
    for (int p = 0; p < linhas; p++) {
        // --- PARTE A: GARANTIR O PIVÔ ---
        // Se o pivô atual for zero, precisamos encontrar um substituto nas linhas abaixo
        if (fabs(matriz[p][p]) < 1e-9) {
            bool achou = false;
            for (int i = p + 1; i < linhas; i++) {
                if (fabs(matriz[i][p]) > 1e-9) {
                    if (troca_linha(matriz, p, i, linhas, colunas) == 1) {
                        (*trocas)++;
                        achou = true;
                        break;
                    }
                }
            }

            if (!achou) {
                return -1;
            }
        }

        // --- REGISTRO DO PASSO (LOG) ---
        atualiza_passo_triangulacao(&passos[*num_passos], *num_passos, p, p, matriz[p][p]);
        (*num_passos)++;

        // --- PARTE B: ELIMINAÇÃO (ZERAR AS LINHAS DE BAIXO) ---
        // Percorre as linhas (i) abaixo do pivô (p)
        for (int i = p + 1; i < linhas; i++) {
            double mult = matriz[i][p] / matriz[p][p];

            // Aplica a subtração na linha (i) inteira
            // Percorre as colunas (k). 
            // DICA: Podemos começar k em 'p' porque antes disso já é tudo zero.
            for (int k = p; k < colunas; k++) {
                matriz[i][k] = matriz[i][k] - (mult * matriz[p][k]);
            }
        }
    }
    
    return 0;
}

void valores_x_retrosubstituicao(double **matriz, double *x, int linhas, int colunas) {
    double soma;

    x[linhas - 1] = matriz[linhas - 1][colunas - 1] / matriz[linhas - 1][linhas - 1];

    soma = 0;
    for(int k = linhas - 2; k >= 0; k--) {
        soma = matriz[k][colunas - 1];

        for(int j = k + 1; j < linhas; j++) {
            soma = soma - (matriz[k][j] * x[j]);
        }
        x[k] = soma / matriz[k][k];
    }
}