/*

	Vitor Albuquerque de Paula 			(8628220)
*/


/*
Este TAD de lista ordenada foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se um grafo
A lista pe organizada em ordem crescente, mantendo sempre o de menor peso no início da lista
*/
#include <stdio.h>
#include <stdlib.h>
#include "../header/global.h"
#include "../header/listaOrd.h"
#include "../header/pilha.h"

/*
Função para inicialização da lista ordenada
Parâmetros:
	lista- lista a ser inicializada
*/
void listaOrd_init(listaOrd_t *lista) {
	lista->ini = NULL;
	lista->numNode = 0;
}

/*
Função para adição de um novo nó na lista
Parâmetros:
	lista- lista na qual se deve adicionar a nova informação
	info- informação a ser adicionada
	peso- peso da nova informação na lista ordenada

Variáveis:
	buff- nó utilizado para alocar nova memória para o nó da nova informação
*/
void listaOrd_add(listaOrd_t *lista, dataLO_t info, double peso, pilha_t buffX, pilha_t buffY) {
	nodeLO_t *buff;

	buff = (nodeLO_t *) _malloc(sizeof(nodeLO_t));
	buff->info = info;
	buff->peso = peso;
	buff->posicaoX = buffX;
	buff->posicaoY = buffY;

	if(lista->ini == NULL) {
		lista->ini = buff;
		buff->prox = NULL;
	} else {
		nodeLO_t *aux;
		nodeLO_t *ant;

		aux = lista->ini;
		ant = NULL;
		while(aux != NULL && peso >= aux->peso) {
			ant = aux;
			aux = aux->prox;
		}

		if(ant == NULL) {
			buff->prox = lista->ini;
			lista->ini = buff;
		} else {
			ant->prox = buff;
			buff->prox = aux;
		}
	}
	lista->numNode++;
}

/*
Função para remover um nó da lista dada como parâmetro na posição indicada
Parâmetros:
	lista- lista da qual será removido no nó
	pos- posição em que está o nó que se deseja remover
	data- posição de memória em que a informação do nó removido será retornado

Variáveis:
	i- contador
	aux, ant- nós para percorrer a lista
*/
void listaOrd_remove(listaOrd_t *lista, unsigned int pos, dataLO_t *data, pilha_t *posicaoX, pilha_t *posicaoY) {
	int i;
	nodeLO_t *aux;
	nodeLO_t *ant;

	aux = lista->ini;
	i = 1;
	while(aux != NULL && i < pos) {
		ant = aux;
		aux = aux->prox;
	}

	if(aux != NULL) {
		*data = aux->info;
		*posicaoX = aux->posicaoX;
		*posicaoY = aux->posicaoY;

		if(i == 1) {
			lista->ini = lista->ini->prox;
			free(aux);

		} else {
			ant->prox = aux->prox;
			free(aux);
		}
		lista->numNode--;
	} else {
		data = NULL;
	}
}

/*
Função para desalocar toda memória ainda alocada para a lista
Parâmetros:
	lista- lista a ser destruída

Variáveis:
	aux, buff- nós para percorrer a lista
*/
void listaOrd_destroy(listaOrd_t *lista) {
	nodeLO_t *aux;
	nodeLO_t *buff;

	aux = lista->ini;
	while(aux != NULL) {
		buff = aux;
		aux = aux->prox;
		free(buff);
	}
}

/*
Função que verifica se uma lista está vazia
Parâmetros:
	lista- lista a ser verificada se está vazia

Retorno:
	1- lista vazia
	0- lista não vazia
*/
int listaOrd_vazia(listaOrd_t *lista) {
	return (lista->numNode)? 0 : 1;
}
