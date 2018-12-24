/*

	Vitor Albuquerque de Paula 			(8628220)
*/

/*
Este TAD de grafo foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se o grafo
*/
#include <stdio.h>

#ifndef GRAFO_H_
#define GRAFO_H_

#include "global.h"
#include "pilha.h"

#define NUM_NODE 4 //número de arestas por nó

//===========================
//direções das arestas do grafo
#define NORTE 0
#define SUL 1
#define LESTE 2
#define OESTE 3
//===========================

#define VAZIA -1 //Número para identificação de uma posição vazia

typedef int data_t;

//Struct que representa um nó do grafo
typedef struct Node {
	data_t info; //informação guardada no grafo (entrada/saída/vazia)
	int *adj; //vetor de nós com os quais este faz conexões no grafo
	int posX; //linha da matriz do nó de destino
	int posY; //coluna da matriz do nó de destino
	double historico; //histórico utilizado na busca A*
} nodeG_t;

//Struct que representa a estrutura do grafo
typedef struct Grafo {
	unsigned int raiz; //nó raiz do grafo
	unsigned int tam; //número de nós no grafo
	nodeG_t *nodes; //vetor de nós do grafo
} grafo_t;

void grafo_init(grafo_t *grafo, unsigned int tam);	//Inicializa o grafo
int grafo_connect(grafo_t *grafo, int a, int b, int dir); //Faz uma conexao entre os nós a e b
void grafo_defRaiz(grafo_t *grafo, unsigned int pos); //Redefine o nó raiz do grafo
int grafo_getAdj(nodeG_t *node, int pos); //Retorna posição do nó adjacente em pos
void grafo_addInfo(grafo_t *grafo, data_t info, unsigned int pos); //Adiciona uma nova informação no grafo
void grafo_print(grafo_t *grafo); //Imprime o grafo
int grafo_conexo(grafo_t *grafo); //Verifica se um grafo é conexo
int grafo_Astar(grafo_t *grafo, int posX, int posY, data_t info, pilha_t *caminhoX, pilha_t * caminhoY); //Realiza busca informada aplicando o algoritmo A*
int grafo_buscaLargura(grafo_t *grafo, data_t info); //Realiza busca em largura
int grafo_buscaProfundidade(grafo_t *grafo, data_t info, pilha_t *caminhoX, pilha_t *caminhoY); //Realiza busca em profundidade
void grafo_destroy(grafo_t *grafo); //Libera memória alocada para o grafo

#endif
