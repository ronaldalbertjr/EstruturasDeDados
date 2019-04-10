#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h> 
#include <ctype.h>

struct pilha
{
	int maxTam;
	int top;
	char* items;

};

struct pilha* novaPilha(int capacidade)
{
	struct pilha *pt = (struct pilha*) malloc(sizeof(struct pilha));

	pt->maxTam = capacidade;
	pt->top = -1;
	pt->items = (char*) malloc(sizeof(char) * capacidade);

	return pt;
};

int tamanho(struct pilha *pt)
{
	return pt->top + 1;
}

int estaVazio(struct pilha *pt)
{
	return pt->top == -1;
}

int estaCheio(struct pilha *pt)
{
	return pt->top 	== pt->maxTam - 1;
}

void inserir(struct pilha *pt, char x)
{
	if(estaCheio(pt))
	{
		char* aux = (char*) malloc(sizeof(char) * pt->maxTam);
		for(int i = 0; i < pt->maxTam; i++)
		{
			aux[i] = pt->items[i];
		}
		pt->maxTam = pt->maxTam * 2;
		pt->items = (char*) malloc(sizeof(char) * pt->maxTam);
		for(int i = 0; i < pt->maxTam / 2; i++)
		{
			pt->items[i] = aux[i];
		}
	}
	
	pt->items[++pt->top] = x;
}

int topo(struct pilha *pt)
{
	if(!estaVazio(pt))
		return pt->items[pt->top];
	else
		exit(EXIT_FAILURE);
}

int remover(struct pilha *pt)
{
	if(estaVazio(pt))
		exit(EXIT_FAILURE);
	
	return pt->items[pt->top--];
}

int main(int argc, char *argv[])
{
	struct pilha *ptNum = novaPilha(50);
	struct pilha *ptNotNum = novaPilha(25);
	char c;

	while(scanf("%c", &c) == 1)
	{
		if(isdigit(c))
			inserir(ptNum, c);
		else
			inserir(ptNotNum, c);
	}

	/* inserir(pt, 'a');
	inserir(pt, 'z');
	inserir(pt, 'b');

	printf("O elemento no topo da pilha é %c\n", topo(pt));
	printf("O tamanho da pilha é %d\n", tamanho(pt));

	char c1 = remover(pt);
	char c2 = remover(pt);
	char c3 = remover(pt);

	printf("Os elementos %c, %c, %c foram removidos\n", c1, c2, c3);

	if(estaVazio(pt))
		printf("Esta Vazio!!!!");
	else
		printf("Não esta Vazio!!!");*/
	
	return 0;
}
