#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;


typedef struct node{
	int valor;
	struct node *esq;
	struct node *dir;
	int altura;
}t_node;

node *criarNode()
{
	node *p = NULL;
	return p;	
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

int calcularAltura(node *n)
{
	if (!(n))  
        return 0;  
    else
    {  
        int eAltura = calcularAltura(n->esq);  
        int dAltura = calcularAltura(n->dir);  
      
        if (eAltura > dAltura)  
            return(eAltura + 1);  
        else return(dAltura + 1);
	}
}

int diferencaAlturas(node *n)
{
	if(!n)
		return 0;
	else
		return calcularAltura(n->esq) - calcularAltura(n->dir);
}

void adicionarElementos(node **n, int x)
{
	node *p = (node*) malloc(sizeof(node));
	p->valor = x;
	p->esq = NULL;
	p->dir = NULL;
	p->altura = 0;

	if(!(*n))
	{ 
		*n = p;
		return;
	}

	else
	{ 
		adicionarElementos(p->valor <= (*n)->valor ? &(*n)->esq : &(*n)->dir, x);
		free(p);
	}

	(*n)->altura = calcularAltura(*n);

	int balanceamento = diferencaAlturas(*n);

	if (balanceamento > 1 && x < (*n)->esq->valor)
	{  
        rotacaoDireita(n);
        return ;  
    }
    if (balanceamento < -1 && x > (*n)->dir->valor)
    {  
        rotacaoEsquerda(n);
        return ;  
    }
    if (balanceamento > 1 && x > (*n)->esq->valor)  
    {  
    	duplaRotacaoDireita(n);
    	return;	  
    }  
   
    if (balanceamento < -1 && x < (*n)->dir->valor)  
    {  
    	duplaRotacaoEsquerda(n);
        return;  
    }  
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
	node *n = criarNode();
	int valor;
	while(!feof(stdin))
	{
		if(scanf("%d", &valor) == 1)
			adicionarElementos(&n, valor);
	}
	preordem(n);
	return 0;
}