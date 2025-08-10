#include <stdio.h>
#include <stdlib.h>

struct ponto {
	float x;
	float y;
};

void mover_ponto(struct ponto *p, float dx, float dy) {
	p->x += dx;
	p->y += dy;
}

int criar_ponto(struct ponto **p, float x, float y) {
	(*p) = malloc(sizeof(struct ponto));
	if (!(*p))
		return 1;
	(*p)->x = x;
	(*p)->y = y;

	return 0;
}

int main() {
	struct ponto *meu_ponto = NULL;

	if(!criar_ponto(&meu_ponto, 8, 2))
		return 1;
	
	mover_ponto(meu_ponto, 5, 3);
	
	printf("Ponto final: (%.2f, %.2f)\n", meu_ponto->x, meu_ponto->y);

	free(meu_ponto);

	return 0;
}
