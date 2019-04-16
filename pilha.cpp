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

struct pilhaInt
{
	int maxTam;
	int top;
	int* items;
};

struct pilha* novaPilha(int capacidade)
{
	struct pilha *pt = (struct pilha*) malloc(sizeof(struct pilha));

	pt->maxTam = capacidade;
	pt->top = -1;
	pt->items = (char*) malloc(sizeof(char) * capacidade);

	return pt;
};

struct pilhaInt* novaPilhaInt(int capacidade)
{
	struct pilhaInt *pt = (struct pilhaInt*) malloc(sizeof(struct pilhaInt));

	pt->maxTam = capacidade;
	pt->top = -1;
	pt->items = (int*) malloc(sizeof(int) * capacidade);

	return pt;	
};

int tamanho(struct pilha *pt)
{
	return pt->top + 1;
}

int tamanhoInt(struct pilhaInt *pt)
{
	return pt->top + 1;
}

int estaVazio(struct pilha *pt)
{
	return pt->top == -1;
}

int estaVazioInt(struct pilhaInt *pt)
{
	return pt->top == -1;
}

int estaCheio(struct pilha *pt)
{
	return pt->top 	== pt->maxTam - 1;
}

int estaCheioInt(struct pilhaInt *pt)
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

void inserirInt(struct pilhaInt *pt, int x)
{
	if (estaCheioInt(pt))
	{
		int* aux = (int*) malloc(sizeof(int) * pt->maxTam);
		for(int i = 0; i < pt->maxTam; i++)
		{
			aux[i] = pt->items[i];
		}
		pt->maxTam = pt->maxTam * 2;
		pt->items = (int*) malloc(sizeof(int) * pt->maxTam);
		for(int i = 0; i < pt->maxTam / 2; i++)
		{
			pt->items[i] = aux[i];
		}
	}

	pt->items[++pt->top] = x;
}
char topo(struct pilha *pt)
{
	if(!estaVazio(pt))
		return pt->items[pt->top];
	else
		exit(EXIT_FAILURE);
}

int topoInt(struct pilhaInt *pt)
{
	if(!estaVazioInt(pt))
		return pt->items[pt->top];
	else
		exit(EXIT_FAILURE);
}

char remover(struct pilha *pt)
{
	if(estaVazio(pt))
		exit(EXIT_FAILURE);
	
	return pt->items[pt->top--];
}

int removerInt(struct pilhaInt *pt)
{
	if(estaVazioInt(pt))
		exit(EXIT_FAILURE);
	
	return pt->items[pt->top--];
}

int charToInt(char x)
{
	 char str[2];

 	str[0] = x;
 	str[1] = '\0';
 	return (int) strtol(str, NULL, 10);
}

struct pilhaInt* notacaoPolonesa(char *c, struct pilhaInt *ptNum, struct pilha *ptNotNum)
{
	int  i = 0;
	int lastWasDigit = 0;

	struct pilhaInt *ptResultado = novaPilhaInt(50);

	while(*(c + i))
	{
		if(isdigit(*(c + i))) 
		{
			if(!lastWasDigit)
			{
				inserirInt(ptNum, charToInt(*(c + i)));
				lastWasDigit = 10;
			}
			else if(lastWasDigit)
			{
				int aux = removerInt(ptNum);
				inserirInt(ptNum, (aux * lastWasDigit) + charToInt(*(c + i)));
			}
		}
		else
		{
			lastWasDigit = 0;
			if(*(c + i) == ')')
			{
				while(true)
				{	
					char aux = remover(ptNotNum);
					if(aux != 40)
						inserirInt(ptNum, (int) aux * -1);
					else
						break;
				}
			}
			else
			{
				inserir(ptNotNum, *(c + i));
			}
		}

		i++;
	}

	int aux;
	while(true)
	{
		if(estaVazioInt(ptNum))
			break;

		aux = removerInt(ptNum);

		inserirInt(ptResultado, aux);
	}	

	return ptResultado;
}

int resolverEquacao(struct  pilhaInt *ptNum)
{
	int n1, n2;
	int aux;
	struct pilhaInt *ptAux = novaPilhaInt(50);
	while(true)
	{
		if(estaVazioInt(ptNum))
			break;


		aux = removerInt(ptNum);
		switch(aux)
		{
			case -42:
				n1 = removerInt(ptAux);
				n2 = removerInt(ptAux);
				inserirInt(ptAux, n2 * n1);
			break;

			case -43:
				n1 = removerInt(ptAux);
				n2 = removerInt(ptAux);
				inserirInt(ptAux, n2 + n1);
			break;

			case -45:
				n1 = removerInt(ptAux);
				n2 = removerInt(ptAux);
				inserirInt(ptAux, n2 - n1);
			break;

			case -47:
				n1 = removerInt(ptAux);
				n2 = removerInt(ptAux);
				inserirInt(ptAux, n2 / n1);
			break;

			default:
				inserirInt(ptAux, aux);
		}

	}

	n1 = removerInt(ptAux);
	return n1;
}

int main(int argc, char *argv[])
{
	struct pilhaInt *ptNum = novaPilhaInt(50);
	struct pilha *ptNotNum = novaPilha(25);
	char *c = (char*) malloc(sizeof(char) * 500);
	
	scanf("%s", c);
	ptNum = notacaoPolonesa(c, ptNum, ptNotNum);

	int resultado = resolverEquacao(ptNum);

	printf("O resultado é %d\n", resultado);

/*
	int j;
	while(true)
	{
		if(estaVazioInt(ptNum))
			break;

		j = removerInt(ptNum);
		printf("%d ", j);
	}

	inserir(pt, 'a');
	inserir(pt, 'z');
	inserir(pt, 'b');https://www.google.com/search?client=ubuntu&channel=fs&q=traduto&ie=utf-8&oe=utf-8

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
