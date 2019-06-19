#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int maior = 0;
struct Elemento
{
	int valor;
	int pai;
	int rank;
	int quantidadeDeElementos;
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

	if(origemX != origemY)
	{
		subconjuntos[origemX].quantidadeDeElementos += subconjuntos[origemY].quantidadeDeElementos;
		subconjuntos[origemY].quantidadeDeElementos = subconjuntos[origemX].quantidadeDeElementos;
	}

	if(subconjuntos[origemX].rank < subconjuntos[origemY].rank)
		subconjuntos[origemX].pai = origemY;
	else if(subconjuntos[origemX].rank > subconjuntos[origemY].rank)
		subconjuntos[origemY].pai = origemX;

	else{
		subconjuntos[origemY].pai = origemX;
		subconjuntos[origemX].rank++;
	}

	maior = maior > subconjuntos[origemX].quantidadeDeElementos ? maior : subconjuntos[origemX].quantidadeDeElementos;
}


int main()
{
	int P;
	scanf("%d", &P);
	int valor0, valor1;

	struct Elemento subconjuntos[P];
	struct Elemento* aux;
	for(int i = 1; i <= P; i++)
	{
		aux = (struct Elemento*) malloc( sizeof(struct Elemento) );
		aux->valor = i;
		aux->pai = i;
		aux->quantidadeDeElementos = 1;
		aux->rank = 0;

		subconjuntos[i] = *aux;
	}

	while(!feof(stdin))
	{
		int d = scanf("%d", &valor0); 
		if(d == 1)
		{
			scanf("%d", &valor1);
			uniao(subconjuntos, valor0, valor1);
		}
		else
		{
			while ( (d = getchar()) != EOF && d != '\n' );
			printf("|%d|\n", maior);
		}
	}
}