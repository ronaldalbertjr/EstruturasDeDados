#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int maior;

struct Elemento
{
	int valor;
	int pai;
	int rank;
};

int find(struct Elemento subconjuntos[], int i)
{
	if(subconjuntos[i].pai != i)
		subconjuntos[i].pai = find(subconjuntos, subconjuntos[i].pai);

	return subconjuntos[i].pai;
}

void uniao(struct Elemento subconjuntos[], int x, int y)
{
	int origemX = find(subconjuntos, x);
	int origemY = find(subconjuntos, y);

	if(subconjuntos[origemX].rank < subconjuntos[origemY].rank)
		subconjuntos[origemX].pai = origemY;
	else if(subconjuntos[origemX].rank < subconjuntos[origemY].rank)
		subconjuntos[origemY].pai = origemX;

	else{
		subconjuntos[origemY].pai = origemX;
		subconjuntos[origemX].rank++;
	}
}


int main()
{
	int P;
	scanf("%d", &P);

	struct Elemento subconjuntos[P];
	for(int i = 0; i < P; i++)
	{
		subconjuntos[i] = (struct Elemento*) malloc( sizeof(struct Elemento) );
		subconjuntos[i]->valor = i + 1;
		subconjuntos[i]->pai = i + 1;
		subconjuntos[i]->rank = 0;
	}
	
}