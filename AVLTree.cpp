#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct node{
	int valor;
	struct node *esq;
	struct node *dir;
}t_node;

node *criarNode(int x)
{
	node *p = (node*) malloc(sizeof(node));
	p->valor = x;
	p->esq = NULL;
	p->dir = NULL;

	return p;	
}

void adicionarElementos(node **n, int x)
{
	node *p = (node*) malloc(sizeof(node));
	p->valor = x;
	p->esq = NULL;
	p->dir = NULL;

	if(!(*n))
	{ 
		*n = p;
		return;
	}

	else{ 
		adicionarElementos(p->valor <= (*n)->valor ? &(*n)->esq : &(*n)->dir, x);
		free(p);
	}
}

void rotacaoEsquerda(node **n)
{
	node *aux;
	aux = (*n)->dir;
	(*n)->dir = (*n)->dir->esq;
	aux->esq = (*n);
	(*n) = aux;
}

void rotacaoDireita(node **n)
{
	node *aux;
	aux = (*n)->esq;
	(*n)->esq = (*n)->esq->dir;
	aux->dir = (*n);
	(*n) = aux;
}

void duplaRotacaoEsquerda(node **n)
{
	rotacaoDireita(&((*n)->dir));
	rotacaoEsquerda(n);
}

void duplaRotacaoDireita(node **n)
{
	rotacaoEsquerda(&((*n)->esq));
	rotacaoDireita(n);
}

void preordem(node *node)
{
	if(node != NULL)
	{
		printf("%d ", node->valor);
		preordem(node->esq);
		preordem(node->dir);
	}
}

int main(int argc, char const *argv[])
{
	node *n = criarNode(5);
	adicionarElementos(&n, 7);
	adicionarElementos(&n, 3);
	adicionarElementos(&n, 2);
	adicionarElementos(&n, 4);
	adicionarElementos(&n, 6);
	adicionarElementos(&n, 8);
	duplaRotacaoEsquerda(&n);
	preordem(n);
	return 0;
}