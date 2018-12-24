/*

	Vitor Albuquerque de Paula 			(8628220)
*/

/*
Este TAD de lista ordenada foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se um grafo
A lista pe organizada em ordem crescente, mantendo sempre o de menor peso no início da lista
*/
#include <stdio.h>
#include "pilha.h"

#ifndef LISTA_ORDENADA_
#define LISTA_ORDENADA_

//tipo de dado guardado na lista
typedef struct DataLO {
	int info;
	int historico;
} dataLO_t;

typedef struct NodeOL {
	double peso; //peso para ordenação da lsita
	dataLO_t info; //informação do nó
	struct NodeOL *prox; //próximo nó da lista
	pilha_t posicaoX; //guarda a posição X para a busca informada
	pilha_t posicaoY; //guarda a posição Y para a busca intformada
} nodeLO_t;

//Struct para representação da lista
typedef struct ListaOrd {
	int numNode; //números de nós na lista
	nodeLO_t *ini; //primeiro nó da lista
} listaOrd_t;

void listaOrd_init(listaOrd_t *lista); //Inicializa a lista
void listaOrd_add(listaOrd_t *lista, dataLO_t info, double peso, pilha_t buffX, pilha_t buffY); //Adciona um novo nó a lista
void listaOrd_remove(listaOrd_t *lista, unsigned int pos, dataLO_t *data, pilha_t *posicaoX, pilha_t *posicaoY); //remove m nó da lista
void listaOrd_destroy(listaOrd_t *lista); //desaloca toda memória da lista
int listaOrd_vazia(listaOrd_t *lista); //Verifica se uma lsita está vazia

#endif //LISTA_ORDENADA_
