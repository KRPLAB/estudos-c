#ifndef TRIANGULACAO_H
#define TRIANGULACAO_H

#include "matriz.h"
#define TAG_TRIANG "LOG_TRIANGULACAO"

/**
 * @brief Estrutura para armazenar informações da etapa de triangulação.
 */
typedef struct {
    int passo;         ///< Número do passo da triangulação
    int linha_pivo;    ///< Índice da linha pivô no passo atual
    int coluna_pivo;   ///< Índice da coluna pivô no passo atual
    double valor_pivo; ///< Valor do elemento pivô
} PassoTriangulacao;

void atualiza_passo_triangulacao(PassoTriangulacao *passo, int passo_num, int linha_pivo, int coluna_pivo, double valor_pivo);

/**
 * @brief Realiza a triangulação de Gauss na matriz.
 * * @param matriz A matriz (linhasxcolunas) que será alterada diretamente.
 * @param passos Array para armazenar o log das operações realizadas.
 * @param num_passos Ponteiro para retornar quantos passos foram registrados.
 * @return int Retorna 0 se sucesso (triangulou), ou código de erro caso contrário.
 */
int triangular_matriz(double **matriz, PassoTriangulacao passos[], int *num_passos, int *trocas, int linhas, int colunas);

void valores_x_retrosubstituicao(double **matriz, double *x, int linhas, int colunas);

#endif