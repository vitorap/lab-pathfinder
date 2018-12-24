/*

	Vitor Albuquerque de Paula 			(8628220)
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/labirinto.h"
#include "../header/grafo.h"
#include "../header/global.h"
#include "../header/pilha.h"

void getAdjBloq(labirinto_t *labrt, int i, int j, int *adj); //Função que retorna em adj as posições das arestas adjascentes com nós que não possui conexões

/*
Função de inicialização das variáveis do labirinto, alocação de sua memória e geração das suas conexões
Parâmetros:
	labrt- estrutura do labirinto a ser inicializado
	lin- número de linhas do labirinto
	col- número de colunas do labirinto

Variáveis:
	i, j, k-  contadores
	pos- usado para guardar posições do labirinto
	adj- vetor com as posições de cada direção no labirinto
	visitadas- número de posições já visitadas na geração das conexões
	buff, aux- variáveis auxiliares
	posicaoX- pilha utilizada para guardar as posições do labirinto na criação de suas conexões na direção X
	posicaoY- pilha utilizada para guardar as posições do labirinto na criação de suas conexões na direção Y
*/
void  labrt_init(labirinto_t *labrt, int lin, int col) {
	int i;
	int j;
	int k;
	int pos;
	int adj[NUM_NODE];
	int visitadas;
	int buff;
	int aux;
	int **matrizVisitados;
	pilha_t posicaoX;
	pilha_t posicaoY;

	/*=========================================================================================================
		Etapa de inicialização das variáveis e de alocação de memória
	*/
	labrt->lin = lin;
	labrt->col = col;

	matrizVisitados = (int **) _malloc(sizeof(int *) * lin);
	labrt->pos = (nodeG_t ***) _malloc(sizeof(nodeG_t **) * lin); //Inicializa matriz do labirinto
	for(i = 0; i < lin; i++) {
		labrt->pos[i] = (nodeG_t **) _malloc(sizeof(nodeG_t *) * col);
		matrizVisitados[i] = (int *) _malloc(sizeof(int) * col);
	}
	grafo_init(&labrt->grafo, lin*col); //Inicializa grafo do labirinto

	k = 0;
	for(i = 0; i < lin; i++) { // Inicializa as posições da matriz do labirinto com os nós do grafo
		for(j = 0; j < col; j++) {
			labrt->pos[i][j] = &labrt->grafo.nodes[k];
			labrt->grafo.nodes[k].posX = i;
			labrt->grafo.nodes[k].posY = j;
			k++;

			matrizVisitados[i][j] = 0;
		}
	}

	srand(time(NULL));
	pos = rand() % lin;
	labrt->entrada = labrt->pos[pos][col-1];
	grafo_defRaiz(&labrt->grafo, (pos*col) + col-1);
	labrt->entrada->info = ENTRADA;

	pos = rand() % lin;
	labrt->saida = labrt->pos[pos][0];
	labrt->saida->info = SAIDA;
	//=========================================================================================================

	/*=========================================================================================================
		Etapa de geração das conexões do labirinto
	*/
	pilha_init(&posicaoX);
	pilha_init(&posicaoY);
	visitadas = 1;
	i = labrt->entrada->posX;
	j = labrt->entrada->posY;
	while(visitadas < labrt->grafo.tam) { //Enquanto o número de nós visitados é menor que o total de nós
		getAdjBloq(labrt, i, j, adj); //Pega os nós adjacentes ao atual que não possuem nenhuma conexão
		if(adj[NORTE] != VAZIA || adj[SUL] != VAZIA || adj[LESTE] != VAZIA || adj[OESTE] != VAZIA) { //Caso haja um nó vizinho que não possui nenhuma conexão
			do { //Escolhe uma ao acaso
				buff = rand() % NUM_NODE;
				pos = adj[buff];
			} while(pos == VAZIA);
			//Empilha posição atual
			pilha_push(&posicaoX, i);
			pilha_push(&posicaoY, j);

			visitadas++;
			matrizVisitados[i][j] = 1;
			//Faz uma conexão entre o nó atual e o que não possui nenhuma conexão e faz deste o próximo nó a ser analizado
			int flag;
			if(buff == SUL || buff == NORTE) {
				flag = grafo_connect(&labrt->grafo, (i*labrt->col) + j, (pos*labrt->col) + j, buff);
				if(flag) {
					exit(-1);
				}
				i = pos;
			} else {
				flag = grafo_connect(&labrt->grafo, (i*labrt->col) + j, (i*labrt->col) + pos, buff);
				if(flag) {
					exit(-1);
				}
				j = pos;
			}


		} else { //Desempilha posição e pega a anterior
			POS:
			if(posicaoX.tam == 0) {
				for(i = 0; i < lin; i++) {
					for(j = 0; j < col; j++) {
						if(matrizVisitados[i][j] == 0) {
							if(i == 0) {
								pilha_push(&posicaoX, i+1);
								pilha_push(&posicaoY, j);
							} else {
								pilha_push(&posicaoX, i-1);
								pilha_push(&posicaoY, j);
							}
							goto POS;
						}
					}
				}
			}

			i = pilha_pop(&posicaoX);
			j = pilha_pop(&posicaoY);
		}
	}
	//=========================================================================================================
	pilha_destroy(&posicaoX);
	pilha_destroy(&posicaoY);
	for(i = 0; i < lin; i++) {
		free(matrizVisitados[i]);
	}
	free(matrizVisitados);
}

/*
Função que procura a saida de forma cega de acordo com o método de busca desejado no grafo com as conexões do labirinto (0-LARGURA | 1-PROFUNDIDADE)
Parametros:
	labrt- labirinto no qual se deseja realizar a busca
	metodo- método pelo qual se deseja realizar a busca

Retorno:
	nó do grafo em que está a saída
*/
int labrt_findSaida(labirinto_t *labrt, int metodo) {
	switch(metodo) {
		case PROFUNDIDADE:
			return grafo_buscaProfundidade(&labrt->grafo, SAIDA, &labrt->caminhoX, &labrt->caminhoY);
			break;

		case INFORMADA:
			return grafo_Astar(&labrt->grafo, labrt->saida->posX, labrt->saida->posY, SAIDA, &labrt->caminhoX, &labrt->caminhoY);
			break;

		default:
			return -1;
			break;
	}
}

/*
Função que retorna em adj as posições das arestas adjascentes com nós que não possui conexões
Parametros:
	labrt- labirinto em que os nós se encontram
	i, j- posição[i][j] em que o nó atual se encontra
	adj- caso o nó adjacente possua conexões ou não exista recebe -1, caso contrário recebe a posição NORTE-SUL ou LESTE-OESTE em que está relacionada com o  nó atual

Variáveis:
	k- contador
*/
void getAdjBloq(labirinto_t *labrt, int i, int j, int *adj) {
	int k;

	for(k = 0; k < NUM_NODE; k++) {
		adj[k] = VAZIA;
	}

	if(i != 0) { //Caso não esteja no extremo norte
		for(k = 0; k < NUM_NODE; k++) {
			if(grafo_getAdj(labrt->pos[i-1][j], k) != VAZIA) {
				break;
			}
		}
		adj[NORTE] = (k == NUM_NODE)? i-1 : VAZIA;
	}
	if(i != labrt->lin-1) { //Caso não esteja no extremo sul
		for(k = 0; k < NUM_NODE; k++) {
			if(grafo_getAdj(labrt->pos[i+1][j], k) != VAZIA) {
				break;
			}
		}
		adj[SUL] = (k == NUM_NODE)? i+1 : VAZIA;
	}
	if(j != 0) {
		for(k = 0; k < NUM_NODE; k++) { //Caso não esteja no extremo oeste
			if(grafo_getAdj(labrt->pos[i][j-1], k) != VAZIA) {
				break;
			}
		}
		adj[OESTE] = (k == NUM_NODE)? j-1 : VAZIA;
	}
	if(j != labrt->col-1) {
		for(k = 0; k < NUM_NODE; k++) { //Caso não esteja no extremo leste
			if(grafo_getAdj(labrt->pos[i][j+1], k) != VAZIA) {
				break;
			}
		}
		adj[LESTE] = (k == NUM_NODE)? j+1 : VAZIA;
	}
}

/*
Função para impressão do labirinto com o caminho encontrado pela última busca
Parâmetros:
	labrt- labirinto a ser impresso com seu caminho

Variáveis:
	i, j- contadores
	caminho- matriz que representa o camiho percorrido com as posições pretencentes ao caminho com 1 e os outros com 0
*/
void labrt_print(labirinto_t *labrt) {
	int i;
	int j;
	int **caminho;

	/*=========================================================================================================
		Alocação de memória e inicialização da matriz para sinalização do caminho percorrido
	*/
	caminho = (int **) _malloc(sizeof(int*) * labrt->lin);
	for(i = 0; i < labrt->lin; i++) {
		caminho[i] = (int *) _malloc(sizeof(int) * labrt->col);
	}
	for(i = 0; i < labrt->lin; i++) {
		for(j = 0; j < labrt->col; j++) {
			caminho[i][j] = 0;
		}
	}

	while(labrt->caminhoX.tam > 0) {
		caminho[pilha_pop(&labrt->caminhoX)][pilha_pop(&labrt->caminhoY)] = 1;
	}
	//=========================================================================================================

	/*=========================================================================================================
		Impressão do topo da linha da matriz
	*/
	for(i = 0; i < labrt->col; i++) {
		printf(" ---");
	}
	printf(" \n");
	//=========================================================================================================

	/*=========================================================================================================
		Impressão das posições SUL, LESTE e OESTE por linha da matriz
	*/
	for(i = 0; i < labrt->lin; i++) {
		for(j = 0; j < labrt->col; j++) {
			/*=================================================================================================
				Impressão da orientação LESTE-OESTE de uma linha da matriz
			*/
			if(labrt->pos[i][j]->adj[OESTE] == VAZIA) {
				printf("|");
			} else {
				printf(" ");
			}
			if(caminho[i][j]) {
				printf(" + ");
			} else {
				printf("   ");
			}
		}
		printf("|\n");
		//=================================================================================================

		/*=================================================================================================
			Impressão da posição SUL de uma linha da matriz
		*/
		for(j = 0; j < labrt->col; j++) {
			if(labrt->pos[i][j]->adj[SUL] == VAZIA) {
				printf(" ---");
			} else {
				printf("    ");
			}
		}
		printf(" \n");
		//=================================================================================================
	}
	//=========================================================================================================

	for(i = 0; i < labrt->lin; i++) {
		free(caminho[i]);
	}
	free(caminho);
}

/*
Função para liberação da memória dalocada para o labirinto
Parametros:
	labrt- labirinto a ter sua memória alocada
*/
void labrt_destroy(labirinto_t *labrt) {
	int i;

	for(i = 0; i < labrt->lin; i++) {
		free(labrt->pos[i]);
	}
	free(labrt->pos);

	pilha_destroy(&labrt->caminhoX);
	pilha_destroy(&labrt->caminhoY);
	grafo_destroy(&labrt->grafo);
}
