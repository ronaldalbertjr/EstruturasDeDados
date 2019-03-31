#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int PalavraMaiorQueOutra(char *palavra1, char *palavra2)
{
	int j = 0;
	while(*(palavra1 + j) && *(palavra2 + j))
	{
		if(*(palavra1 + j) < *(palavra2 + j))
			return 1;		
		else if(*(palavra1 + j) > *(palavra2 + j))
			return -1;
		j++;
	}
	return 0;
}

void printLista(char **listaOrdenada)
{
	int j = 0;
	int i = 0;
	char *palavraAtual = (char *) malloc(100 * sizeof(char));

	while(true)
	{
		if(*(listaOrdenada + j) == NULL)
			break;
		strcpy(palavraAtual, *(listaOrdenada + j));
		i = 0;
		while(PalavraMaiorQueOutra(palavraAtual, *(listaOrdenada + j + i)) == 0)
		{ 
			i++;
			if(*(listaOrdenada + j + i) == NULL)
				break;
		}
		printf("%s | %d\n", *(listaOrdenada + j), i);
		j += i;
	}
}

void adicionarPalavraLista(char **listaOrdenada, char *palavraParaAdicionar)
{
	int posicaoASerAdicionada = -1;
	char *ultimaPalavra = (char *) malloc(100 * sizeof(char)), *temp = (char *) malloc(100 * sizeof(char));
	if(*(listaOrdenada) == NULL)
	{ 
		*(listaOrdenada) = (char *) malloc(100 * sizeof(char));
		strcpy(*(listaOrdenada), palavraParaAdicionar);
	}
	else
	{	
		int j = 0;
		while(true)
		{
			if((*(listaOrdenada + j) == NULL || PalavraMaiorQueOutra(*(listaOrdenada + j), palavraParaAdicionar) == -1) && (posicaoASerAdicionada == -1))
			{
				posicaoASerAdicionada = j;
				if(*(listaOrdenada + j) == NULL)
				{
					*(listaOrdenada + j) = (char *)malloc(100 * sizeof(char));
					break;
				}
				strcpy(ultimaPalavra, *(listaOrdenada + j));
			}
			if(posicaoASerAdicionada != -1)
			{
				if(*(listaOrdenada + j + 1) == NULL)
				{
					*(listaOrdenada + j + 1) = (char *) malloc(100 * sizeof(char));
					strcpy(*(listaOrdenada + j + 1), ultimaPalavra);
					break;
				}
				strcpy(temp, *(listaOrdenada + j + 1));
				strcpy(*(listaOrdenada + j + 1), ultimaPalavra);
				strcpy(ultimaPalavra, temp);
			}
			j++;
		}
		strcpy(*(listaOrdenada + posicaoASerAdicionada), palavraParaAdicionar);
	}
}

int main(int argc, char *argv[])
{
	char palavra[100];
	char **listaOrdenada;
	listaOrdenada = (char **) malloc(600 * sizeof(char *));

	while(!feof(stdin))
	{
		if(scanf("%s", palavra) == 1)
		{
			adicionarPalavraLista((char **) listaOrdenada, palavra);
		}
	}
	
	printLista((char **)listaOrdenada);

	return 0;
}
