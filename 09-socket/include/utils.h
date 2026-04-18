/**
 * @file utils.h
 * @brief Funções utilitárias para servidor socket TCP.
 * @author Kauan da Rosa Paulino
 */

#ifndef UTILS_H 
#define UTILS_H

/**
 * @brief tokeniza string usando delimitadores e retorna ponteiro para o próximo token
 * @param str string a ser tokenizada (deve ser modificável)
 * @param delimiters string contendo os caracteres delimitadores
 * @return ponteiro para o próximo token ou NULL se não houver mais tokens
 */
char *tokenize(char *str, const char *delimiters);

/**
 * @brief Verifica primeira linha de requisição e retorna enum do método correto
 * @param *first_line Primeira linha do header da requisição
 * @return Metodo da requisição (GET, POST, PUT, PATCH, DELETE)
 */
int identify_method(const char *first_line);

/**
 * @brief Envia todos os bytes de um buffer através de um socket
 * @param s socket
 * @param buf buffer contendo os dados a serem enviados
 * @param len ponteiro para o tamanho do buffer
 * @return 0 em caso de sucesso, -1 em caso de erro
 */
int utils_send_all(int s, char *buf, int *len);
#endif
