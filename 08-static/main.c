/* Video-aula referencia: https://youtu.be/9RKcGuo7Hrw */
#include <stdio.h>
#include <stdlib.h>

/* Usando a mesma lógica de static ser acessível apenas
 * no escopo da função, uma static que seja declarada
 * globalmente só pode ser acessível no próprio arquivo 
 */
static int valor = 50;

/*Visível em outros arquivos
 */
int valor2 = 25;

float media_pares(int vet[], int tam) {
	/* Apesar de só ter o valor declarado uma
	 * unica vez e poder ser reincrementado, isso
	 * só pode ocorrer dentro do escopo da função
	 */
	static int soma = 0;
	static int quant = 0;

	if(tam == 0)
		return (soma * 1.0) / quant;
	else {
		if(vet[tam-1] % 2 == 0) {
			soma += vet[tam-1];
			quant++;
			return media_pares(vet, tam - 1);
		}
		else {
			return media_pares(vet, tam - 1);
		}
	}
}

int main(void) {
	int vet[6] = {2, 4, 38, 7, 11, 9};

	printf("Media dos pares: %.2f\n", media_pares(vet, 6));

	return 0;
}
