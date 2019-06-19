#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;


typedef struct node{
	int valor;
	int cor;
	struct node *esq;
	struct node *dir;
	struct node *pai;
}t_node;

node *criarNode(int valor)
{
	node *n = (node*) malloc(sizeof(node));
	n->cor = 1;
	n->valor = valor;
	n->esq = n->dir = n->pai = NULL;
	return n;	
}

node* adicionarNaArvoreBinaria(node* raiz, node* n)
{
	if(raiz == NULL)
		return n;

	if(n->valor < raiz->valor)
	{
		raiz->esq = adicionarNaArvoreBinaria(raiz->esq, n);
		raiz->esq->pai = raiz;
	}
	else if(n->valor > raiz->valor)
	{
		raiz->dir = adicionarNaArvoreBinaria(raiz->dir, n);
		raiz->dir->pai = raiz;
	}

	return raiz;
}

void rotacaoEsquerda(node **raiz, node *n)
{
	node *x = n->dir;
	
	n->dir = x->esq;

	if(n->dir != NULL)
		n->dir->pai = n;

	x->pai = n->pai;

	if(n->pai == NULL)
		(*raiz) = x;

	else if(n == n->pai->esq)
		n->pai->esq = x;

	else n->pai->dir = x;

	x->esq = n;
	n->pai = x;
}

void rotacaoDireita(node **raiz, node *n)
{
	node *x = n->esq;

	n->esq = x->dir;

	if(x->dir != NULL)
		x->dir->pai = n;

	x->pai = n->pai;

	if(x->pai == NULL)
		(*raiz) = x;

	else if(n == n->pai->esq)
		n->pai->esq = x;

	else n->pai->dir = x;

	x->dir = n;
	n->pai = x;
}

void consertarAdicionar(node **raiz, node *n)
{
	node *pai = NULL;
	node *avo = NULL;

	while ((n != *raiz) && (n->cor != 0) && (n->pai->cor == 1))
	{
		pai = n->pai;
		avo = n->pai->pai;

		if(pai == avo->esq)
		{
			node *tio = avo->dir;

			if(tio != NULL && tio->cor == 1)
			{
				avo->cor = 1;
				pai->cor = 0;
				tio->cor = 0;
				n = avo;
			}

			else
			{
				if(n == pai->dir)
				{
					rotacaoEsquerda(raiz, pai);
					n = pai;
					pai = n->pai;
				}

				rotacaoDireita(raiz, avo);
				swap(pai->cor, avo->cor);
				n = pai;
			}
		}

		else
		{
			node *tio = avo->esq;

			if(tio != NULL && tio->cor == 1)
			{
				avo->cor = 1;
				pai->cor = 0;
				tio->cor = 0;
				n = avo;
			}

			else
			{
				if(n == pai->esq)
				{
					rotacaoDireita(raiz, pai);
					n = pai;
					pai = n->pai;
				}

				rotacaoEsquerda(raiz, avo);
				swap(pai->cor, avo->cor);
				n = pai;
			}
		}
	}
	(*raiz)->cor = 0;
}

void adicionarElementos(node **raiz, int x)
{
	node *n = criarNode(x);

	(*raiz) = adicionarNaArvoreBinaria((*raiz), n);

	consertarAdicionar(raiz, n);
}

void preordem(node *node)
{
	char c;
	if(node != NULL)
	{
		c = node->cor ? 'R' : 'N'; 
		printf("|%d%c|\n", node->valor, c);
		preordem(node->esq);
		preordem(node->dir);
	}
}

int main(int argc, char const *argv[])
{
	node *n = NULL;
	int valor;
	while(!feof(stdin))
	{
		if(scanf("%d", &valor) == 1)
			adicionarElementos(&n, valor);
	}

	preordem(n);
	return 0;
}