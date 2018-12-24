/*

	Vitor Albuquerque de Paula 			(8628220)
*/


#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../header/pilha.h"
#include "../header/labirinto.h"

int main(void) {
	int lin;
	int col;
	clock_t c1;
	clock_t c2;
	labirinto_t labrt;

	/*=========================================================================================================
		Pega as informações necessárias para gerar o labirinto
	*/
	printf("\e[1;1H\e[2J");
	printf("#####Digite as informacoes pedidas para gerar um labirinto aleatoriamente e encontrar a saida por dois metodos de busca#####\n\n");
	printf("Digite o numero de linhas do labirinto: ");
	scanf("%d", &lin);
	printf("\n");
	printf("Digite o numero de colunas do labirinto: ");
	scanf("%d", &col);
	printf("\n");
	//=========================================================================================================

	labrt_init(&labrt, lin, col); //inicializa o labirinto com as dimensões entradas no programa
	printf("\e[1;1H\e[2J");
	printf("Tamanho do labirinto: labirinto[%d][%d]\n", lin, col);
	printf("Entrada: no[%d][%d]\n", labrt.entrada->posX, labrt.entrada->posY); //Imprime qual é o nó de entrada
	printf("Saida:   no[%d][%d]\n", labrt.saida->posX, labrt.saida->posY); //Imprime qual é o nó de saída


	printf("---------- Busca em profundidade (Busca cega) ---------\n");
	c1 = clock();
	labrt_findSaida(&labrt, PROFUNDIDADE); //realiza busca cega em profundidade
	c2 = clock();
	labrt_print(&labrt); //Imprime labirinto
	printf("Tempo tomado na busca: %lfs\n", ((double)c2 - c1)/CLOCKS_PER_SEC); //imprime tempo tomado pela pesquisa


	printf("-------------- Busca A* (Busca informada) -------------\n");
	c1 = clock();
	labrt_findSaida(&labrt, INFORMADA); //realiza busca informada (busca A*)
	c2 = clock();
	labrt_print(&labrt); //Imprime o labirinto
	printf("Tempo tomado na busca: %lfs\n", ((double)c2 - c1)/CLOCKS_PER_SEC); //imprime o tempo tomado pela pesquisa

	labrt_destroy(&labrt); //libera a memória alocada para aa pesquisa
	return 0;
}
