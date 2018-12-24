/*

	Vitor Albuquerque de Paula 			(8628220)
*/


/*
Este TAD de grafo foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se o grafo
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/grafo.h"
#include "../header/fila.h"
#include "../header/pilha.h"
#include "../header/listaOrd.h"
#include "../header/global.h"

int dir_oposta(int dir); //Função que retorna a direção oposta a direção desejada
int buscaProfundidade(grafo_t *grafo, int node, data_t info, int *visitados, int *nVisitados, pilha_t *caminhoX, pilha_t *caminhoY); //Função que realiza uma busca em profundidade no grafo a partir do nó raiz de forma recursiva
double fAval(int posX, int posY, dataLO_t buff, nodeG_t *node); //Função de avaliação que retorna o somatório do histórico da busca de um nó e de quanto falta para chegar nele

/*
Função de inicialização das variáveis do grafo e de alocação de sua memória
Parâmetros:
	grafo- grafo a ser inicializado
	tam- número de nós do grafo

Variáveis:
	i, j- contadores
*/
void grafo_init(grafo_t *grafo, unsigned int tam) {
	int i;
	int j;

	grafo->raiz = 0;
	grafo->tam = tam;
	grafo->nodes = (nodeG_t *) _malloc(sizeof(nodeG_t) * tam);
	for(i = 0; i < tam; i++) { //Percorre todos os nós do grafo
		grafo->nodes[i].info = VAZIA;
		grafo->nodes[i].adj = (int *) _malloc(sizeof(int) * NUM_NODE);
		for(j = 0; j < NUM_NODE; j++) { //Percorre cada aresta de cada nó
			grafo->nodes[i].adj[j] = VAZIA;
			grafo->nodes[i].historico = 0;
		}
	}
}

/*
Função para redefinição de um nó do grafo como raiz
Parâmetros:
	grafo- grafo a ter sua raíz redefinida
	pos- nova raíz do grafo
*/
void grafo_defRaiz(grafo_t *grafo, unsigned int pos) {
	if(pos < grafo->tam) { //Caso a posição seja válida
		grafo->raiz = pos;
	}
}

/*
Função que retorna valor da aresta de um nó do grafo
Parâmetros:
	node- nó do qual se quer a aresta
	pos- posição da aresta

Retorno:
	Retorna o valor da posição da aresta
*/
int grafo_getAdj(nodeG_t *node, int pos) {
	return node->adj[pos];
}

/*
Função que conecta dois nós do grafo
Parâmetros:
	grafo- grafo no qual estão os nós a serem conectados
	a, b- nós a serem conectados
	dir- direção em relação a 'a' em que os nós serão conectados
*/
int grafo_connect(grafo_t *grafo, int a, int b, int dir) {
	if(grafo->nodes[a].adj[dir] == VAZIA && grafo->nodes[b].adj[dir_oposta(dir)] == VAZIA) {
		grafo->nodes[a].adj[dir] = b;
		grafo->nodes[b].adj[dir_oposta(dir)] = a;
		return 0;
	} else {
		return 1;
	}
}

/*
Função que adiciona uma informação a um nó do grafo
Parâmetros:
	grafo- grafo no qual está o nó em que será adicionada a informação
	info- informação a ser adicionada
	pos- nó em que a informação será adicionada
*/
void grafo_addInfo(grafo_t *grafo, data_t info, unsigned int pos) {
	if(pos <= grafo->tam) { //Se a posição é válida
		grafo->nodes[pos].info = info;
	}
}

/*
Função que imprime as arestas de cada nó numa linha
Parâmetro:
	grafo- grafo a ser impresso

Variáveis:
	i, j- contadores utilizados para percorrer o grafo
*/
void grafo_print(grafo_t *grafo) {
	int i;
	int j;

	for(i = 0; i < grafo->tam; i++) { //Percorre os nós do grafo
		for(j = 0; j < NUM_NODE; j++) { //Percorre as arestas de cada nó
			printf("%d, ",grafo->nodes[i].adj[j]);
		}
		printf("\n");
	}
}

/*
Função de avaliação que caucula a soma do histórico de um ramo da busca com a distância que ainda se está do ńó de destino numa matriz
Parâmetros:
	posX- linha da matriz do nó de destino
	posY- coluna da matriz do nó de destino
	buff- struct com os dados de histŕico e posição do nó atual (com o que quer se comparar)
	node- nó atual (com o que quer se comparar)

retorno:
	Retona o somatório da distância em que se está do nó de destino com o que já se andou para chegar até esse nó
*/
double fAval(int posX, int posY, dataLO_t buff, nodeG_t *node) {
	return sqrt(pow(node->posX - posX, 2) + pow(node->posY - posY, 2)) + (double) buff.historico;
}

/*
Função que busca um nó a partir do nó raiz através do algoritmo de busca informada A* tendo como detino no nó[posX][posY] da matriz de nós
	Para a realização dessa pesquisa, utiliza-se uma lista ordenada na ordem crescente em peso, mantendo o nó com menor valor de função de avaliação no início da lista,
	sendo que o peso é o histórico de quanto já se andou na pesquisa até esse nó
	Como as arestas não possuem peso, a cada novo nó soma-se 1 ao histórico da pesquisa
Parâmetros:
	grafo- grafo em que se realiza a busca
	posX- linha da matriz do nó de destino
	posY- coluna da matriz do nó de destino
	info- informação buscada na pesquisa

Variáveis:
	i- contador
	visitados- vetor booleano que é verdadeiro caso uma posição correspondente no grafo tenha sido visitada e falso caso contrário
	aVisitar- lista ordenada em ordem cresente de peso utilizada para guardar os próximos nós a serem visitados na busca
	data- struct com informação da posição o nó na matriz e do quanto já se andou na pesquisa até ele
*/
int grafo_Astar(grafo_t *grafo, int posX, int posY, data_t info, pilha_t *caminhoX, pilha_t * caminhoY) {
	int i;
	int *visitados;
	listaOrd_t aVisitar;
	dataLO_t data;
	pilha_t buffX;
	pilha_t buffY;

	visitados = (int *) _calloc(sizeof(int), grafo->tam);
	listaOrd_init(&aVisitar);

	data.info = grafo->raiz;
	data.historico = 0;
	pilha_init(caminhoX);
	pilha_init(caminhoY);
	pilha_init(&buffX);
	pilha_init(&buffY);
	listaOrd_add(&aVisitar, data, fAval(posX, posY, data, &grafo->nodes[data.info]), buffX, buffY);
	while(!listaOrd_vazia(&aVisitar)) { //Enquanto há nós a serem visitados
		listaOrd_remove(&aVisitar, 0, &data, &buffX, &buffY); //Pega próximo nó

		pilha_push(&buffX, grafo->nodes[data.info].posX);
		pilha_push(&buffY, grafo->nodes[data.info].posY);

		if(grafo->nodes[data.info].info == info) { //Caso a informação tenha sido encontrada
			free(visitados);
			listaOrd_destroy(&aVisitar);
			while(buffX.tam != 0) {
				pilha_push(caminhoX, pilha_pop(&buffX));
				pilha_push(caminhoY, pilha_pop(&buffY));
			}
			pilha_destroy(&buffX);
			pilha_destroy(&buffY);
			return data.info;
		} else {
			data.historico++;
			visitados[data.info] = 1;
		}

		for(i = 0; i < NUM_NODE; i++) { //Percorre as arestas do nó
			if(grafo->nodes[data.info].adj[i] != VAZIA && !visitados[grafo->nodes[data.info].adj[i]]) {
				dataLO_t buff;

				buff.info = grafo->nodes[data.info].adj[i];
				buff.historico = data.historico + 1;
				listaOrd_add(&aVisitar, buff, fAval(posX, posY, buff, &grafo->nodes[buff.info]), buffX, buffY); //Coloca nós não visitados na fila
			}
		}
	}
	//Não foi encontrada a informação buscada
	free(visitados);
	listaOrd_destroy(&aVisitar);
	return -1;
}

/*
Função que aplica uma busca em largura no grafo a partir do nó raiz
Parâmetros:
	grafo- grafo em que é feita a busca
	info- informação buscada

Variáveis:
	i- contador
	pos- utilizado para indicar posições no grafo
	visitados- vetor booleano que é verdadeiro caso uma posição correspondente no grafo tenha sido visitada e falso caso contrário
	aVisitar- fila utilizada para guardar os próximos nós a serem visitados na busca

Retorno:
	posição do nó em que se encontra a informação
	-1- informação não encontrada
*/
int grafo_buscaLargura(grafo_t *grafo, data_t info) {
	int i;
	int pos;
	int *visitados;
	fila_t aVisitar;

	visitados = (int *) _calloc(sizeof(int), grafo->tam);
	fila_init(&aVisitar, grafo->tam);

	pos = grafo->raiz;
	fila_add(&aVisitar, pos);
	while(!fila_vazia(&aVisitar)) { //Enquanto há nós a serem visitados
		fila_remove(&aVisitar, &pos); //Pega próximo nó
		if(grafo->nodes[pos].info == info) { //Caso a informação tenha sido encontrada
			free(visitados);
			fila_destroy(&aVisitar);
			return pos;
		} else {
			visitados[pos] = 1;
		}

		for(i = 0; i < NUM_NODE; i++) { //Percorre as arestas do nó
			if(grafo->nodes[pos].adj[i] != VAZIA && !visitados[grafo->nodes[pos].adj[i]]) {
				fila_add(&aVisitar, grafo->nodes[pos].adj[i]); //Coloca nós não visitados na fila
			}
		}
	}
	free(visitados);
	fila_destroy(&aVisitar);
	return -1;
}

/*
Função que faz a chamada da função que realiza uma busca em profundidade no grafo a partir do nó raiz de forma recursiva
Parametros:
	grafo- grafo no qual a busca deve ser realizada
	info- informação a ser buscada

Variáveis:
	visitados- vetor booleano que é verdadeiro caso uma posição correspondente no grafo tenha sido visitada e falso caso contrário
	nVisitados- guarda número de nós já visitados
	retorno- guarda retorno da função recursiva

Retorno:
	posição do nó onde a informação se encontra
	-1- informação não encontrada
*/
int grafo_buscaProfundidade(grafo_t *grafo, data_t info, pilha_t *caminhoX, pilha_t *caminhoY) {
	int *visitados;
	int nVisitados;
	int retorno;

	pilha_init(caminhoX);
	pilha_init(caminhoY);
	nVisitados = 0;
	visitados = (int *) _calloc(sizeof(int), grafo->tam);
	retorno  = buscaProfundidade(grafo, grafo->raiz, info, visitados, &nVisitados, caminhoX, caminhoY);
	free(visitados);
	return retorno;
}

/*
Função que realiza uma busca em profundidade no grafo a partir do nó raiz de forma recursiva
Parametros:
	grafo- grafo no qual a busca deve ser realizada
	node- nó no qual a busca se encontra
	info- informação a ser buscada
	visitados- vetor booleano que é verdadeiro caso uma posição correspondente no grafo tenha sido visitada e falso caso contrário
	nVisitados- guarda número de nós já visitados

Variáveis:
	i- contador
	retorno- guarda retorno da chamada recursiva

Retorno:
	posição do nó onde a informação se encontra
	-1- informação não encontrada
*/
int buscaProfundidade(grafo_t *grafo, int node, data_t info, int *visitados, int *nVisitados, pilha_t *caminhoX, pilha_t *caminhoY) {
	int i;
	int retorno;


	if(grafo->nodes[node].info == info) { //Se a informação foi encontrada
		pilha_push(caminhoX, grafo->nodes[node].posX);
		pilha_push(caminhoY, grafo->nodes[node].posY);
		return node;
	}
	if(*nVisitados == grafo->tam) { //Informação não encontrada
		return -1;
	}
	visitados[node] = 1;
	(*nVisitados)++;
	for(i = 0; i < NUM_NODE; i++) { //Percorre as arestas de cada nó
		if(grafo->nodes[node].adj[i] != VAZIA && !visitados[grafo->nodes[node].adj[i]]) { //Garante que a busca será feita no próximo nó não visitado mais a esquerda
			retorno = buscaProfundidade(grafo, grafo->nodes[node].adj[i], info, visitados, nVisitados, caminhoX, caminhoY);
			if(retorno >= 0) {
				pilha_push(caminhoX, grafo->nodes[node].posX);
				pilha_push(caminhoY, grafo->nodes[node].posY);
				return retorno;
			}
		}
	}
	return -1; //Informação não encontrada a partir do nó
}

/*
Função baseada na busca em largura que verifica se um grafo é conexo (ao invés de buscar uma informação,
	verifica se todos os nós são visitados caso uma busca não seja bem sucedida)
Parâmetros:
	grafo- grafo a ser verificado

Variáveis:
	i- contador
	pos- utilizado para indicar posições no grafo
	conexo- booleano que guarda se o grafo é conexo
	visitados- vetor booleano que é verdadeiro caso uma posição correspondente no grafo tenha sido visitada e falso caso contrário
	aVisitar- fila utilizada para guardar os próximos nós a serem visitados na busca

Retorno:
	1- grafo é conexo
	0- grafo não é conexo
*/
int grafo_conexo(grafo_t *grafo) {
	int i;
	int pos;
	int conexo;
	int *visitados;
	fila_t aVisitar;

	visitados = (int *) _calloc(sizeof(int), grafo->tam);
	fila_init(&aVisitar, grafo->tam);

	pos = grafo->raiz;
	fila_add(&aVisitar, pos);
	while(!fila_vazia(&aVisitar)) { //Enquanto há nós a serem visitados na fila
		fila_remove(&aVisitar, &pos); //Pega próximo nó
		visitados[pos] = 1;

		for(i = 0; i < NUM_NODE; i++) { //Percorre as arestas do nó
			if(grafo->nodes[pos].adj[i] != VAZIA && !visitados[grafo->nodes[pos].adj[i]]) {
				fila_add(&aVisitar, grafo->nodes[pos].adj[i]); //Coloca nós não visitados na fila
			}
		}
	}

	conexo = 1;
	for(i = 0; i < grafo->tam; i++) { //Verifica se todos os  nós foram visitados
		if(!visitados[i]) {
			conexo = 0;
			break;
		}
	}

	free(visitados);
	fila_destroy(&aVisitar);
	return conexo;
}

/*
Função que libera toda memória alocada pelo grafo
Parametros:
	grafo- grafo a ter sua memória liberada

Variáveis:
	i- contador
*/
void grafo_destroy(grafo_t *grafo) {
	int i;

	for(i = 0; i < grafo->tam; i++) { //Percorre todos os nós do grafo
		free(grafo->nodes[i].adj);
	}
	free(grafo->nodes);
}

/*
Função que retorna a direção oposta a direção desejada
Parametros:
	dir- direção original

Retorno:
	direção oposta a dir
*/
int dir_oposta(int dir) {
	switch(dir) {
		case NORTE:
			return SUL;
			break;

		case SUL:
			return NORTE;
			break;

		case LESTE:
			return OESTE;
			break;

		case OESTE:
			return LESTE;
			break;

		default:
			return -1;
			break;
	}
}
