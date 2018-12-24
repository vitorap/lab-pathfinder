/*

	Vitor Albuquerque de Paula 			(8628220)
*/


/*
Este TAD de fila foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se um grafo
*/
#include <stdio.h>

#ifndef FILA_H_
#define FILA_H_

//Tipo de dado guardado na fila
typedef int dataF_t;

//Estrutura da fila
typedef struct Fila {
	int ini; //posicao do vetor que é o inicio da fila
	int fim; //posicao do vetor que é o final da fila (sempre vazio)
	int tam; //posicao do vetor que guarda o tamanho total da fila utilizável + 1
	dataF_t *fila; //Vetor que guarda a fila
} fila_t;

void fila_init(fila_t *fila, int tam);	//Inicializa a fila
int fila_add(fila_t *fila, dataF_t info);	//Adiciona uma nova informação a fila
void fila_remove(fila_t *fila, dataF_t *retorno); //Remove uma informação da fila e a coloca em *retorno
void fila_print(fila_t *fila);	//Imprime a fila
void fila_destroy(fila_t *fila); //Libera a memória alocada para a fila

#endif
