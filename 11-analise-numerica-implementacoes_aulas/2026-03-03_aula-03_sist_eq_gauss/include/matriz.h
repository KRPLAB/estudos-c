#ifndef MATRIZ_H
#define MATRIZ_H

#define TAG_MATRIZ "LOG_MATRIZ"

/**
 * @brief Função responsável por fazer leitura de uma matriz
 * 
 * Esta função lê os elementos de uma matriz quadrada 
 * de dimensão linhas x colunas armazenando os valores na matriz fornecida.
 * 
 * @param m Matriz de dimensão linhas x colunas onde os valores serão armazenados
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 */
void leitura_matriz(double **m, int linhas, int colunas);

/**
 * @brief Função responsável por imprimir uma matriz
 * 
 * Esta função imprime os elementos de uma matriz quadrada formatados
 * de forma legível na saída padrão.
 * 
 * @param m Matriz de dimensão linhas x colunas a ser impressa
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 */
void impressao_matriz(double **m, int linhas, int colunas);

/**
 * @brief Função responsável por trocar duas linhas de uma matriz
 * 
 * Esta função troca as linhas linha1 e linha2 da matriz m.
 * A estratégia, para não precisar de uma matriz auxiliar, é trocar os ponteiros das linhas.
 */
int troca_linha(double **m, int linha1, int linha2, int linhas, int colunas);

#endif