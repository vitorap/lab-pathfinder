/*

	Vitor Albuquerque de Paula 			(8628220)
*/


/*
Este TAD de pilha foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se um grafo
*/
#include <stdio.h>
#include <stdlib.h>
#include "../header/pilha.h"

/*
Função de inicialização da pilha
Parametros:
	p- pilha a ser inicializada
*/
void pilha_init(pilha_t *p) {
	p->top = NULL;
	p->tam = 0;
}

/*
Função de inserção na pilha
Parametros:
	p- pilha a ser inicializada
	info- informação a ser inserida na pilha

Variáveis:
	new- novo nó da pílha

Retorno:
	-1: erro ao alocar espaço na memória
	0: Operação finalizada com sucesso
*/
int pilha_push(pilha_t *p, dado_t info) {
	no_t *new;

	new = (no_t *) malloc(sizeof(no_t)); //Cria o no e verifica se foi possivel criá-lo
	if (new == NULL) {
		return ERRO_ALOCACAO;
	}
	new->info = info;

	if(p->top != NULL) {
		new->prox = p->top;
	} else {
		new->prox = NULL;
	}
	p->top = new; //Coloca o novo nó no topo da pilha
	p->tam++;

	return 0;
}

/*
Função que retira dados da pilha e os passa como retorno da funcao
Parametros:
	p- pilha da qual se deve retirar a informação

Variaveis:
	buff- nó para manusear o nó que deverá ser retirado
	info- informação que é retirada da pilha

Retorno:
	Dado retirado na pilha ou erro se a pilha está vazia
*/
dado_t pilha_pop(pilha_t *p) {
	no_t *buff;
	dado_t info;

	buff = p->top;
	if(buff != NULL) {
		p->top = buff->prox;
		info = buff->info;
		free(buff);
		p->tam--;
		return info;
	} else {
		return ERRO_VAZIA;
	}
}

/*
Função para finalizar a pilha (desalocar toda sua memória alocada)
Parametros:
	p- pilha a ser finalizada

Variáveis:
	buff- nó usado na desalocaçao de memória
	aux- nó auxiliar para possibilitar a exclusão dos nós
*/
void pilha_destroy(pilha_t *p) {
	no_t *buff;
	no_t *aux;

	p->tam = 0;
	buff = p->top;
	while(buff != NULL) {
		aux = buff;
		buff = buff->prox;
		free(aux);
	}
}

/*
Função que imprime a pilha
Parametros:
	p- pilha a ser impressa
	buff- no utilizado para navegar pelos nos da pilha
*/
void pilha_print(pilha_t *p) {
	no_t *buff;

	printf("Ha %d dados:\n", p->tam);
	buff = p->top;
	while(buff != NULL) {
		printf("%d; ", buff->info);
		buff = buff->prox;
	}
}
