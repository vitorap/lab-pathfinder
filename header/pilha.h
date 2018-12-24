/*

	Vitor Albuquerque de Paula 			(8628220)
*/

/*
Este TAD de pilha foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se um grafo
*/
#include <stdio.h>

#ifndef PILHA_H_
#define PILHA_H_

#define ERRO_ALOCACAO -1
#define ERRO_VAZIA -2

//definicao do dado que é guardado na pilha
typedef int dado_t;

//definicao do no da pilha
typedef struct No {
	dado_t info;
	struct No *prox;
} no_t;

//definicao da pilha
typedef struct Pilha {
	no_t *top;
	int tam;
} pilha_t;

//Funções do TAD
void pilha_init(pilha_t *p); 				//inicializa a pilha
int pilha_push(pilha_t *p, dado_t info);	//insere na pilha
dado_t pilha_pop(pilha_t *p);				//retira da pilha
void pilha_destroy(pilha_t *p);				//finaliza a pilha
void pilha_print(pilha_t *p);		//imprime a pilha

#endif //PILHA_H_
