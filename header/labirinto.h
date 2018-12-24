/*

	Vitor Albuquerque de Paula 			(8628220)
*/


#include <stdio.h>
#include "grafo.h"

#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#define ENTRADA 1 //valor que indica que o nó é a entrada do labirinto
#define SAIDA 2 //valor que indica que o nó é a saida do labirinto
//Identificação do tipo de busca
#define LARGURA 0
#define PROFUNDIDADE 1
#define INFORMADA 2

//Definição da estrutura que representa o labirinto
typedef struct Labirinto {
	int lin; //numero de linhas na matriz do labirinto
	int col; //numero de colunas na matriz do labirinto
	grafo_t grafo; //grafo com as conexões do labirinto
	nodeG_t ***pos; //matriz com as posições do labirinto
	nodeG_t *entrada; //nó de entrada do labirinto
	nodeG_t *saida; //nó de saida do labirinto
	pilha_t caminhoX;
	pilha_t caminhoY;
} labirinto_t;

void  labrt_init(labirinto_t *labrt, int lin, int col); //Inicializa o labirinto
int labrt_findSaida(labirinto_t *labrt, int metodo); //Encontra a saida a partir do nó de entrada
void labrt_print(labirinto_t *labrt); //Funão para impressão do labirinto com o último caminho encontrado pela última busca
void labrt_destroy(labirinto_t *labrt); //Libera toda a memória alocada para o labirinto

#endif
