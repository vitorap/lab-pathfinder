/*

	Vitor Albuquerque de Paula 			(8628220)
*/

/*
Este TAD de fila foi adaptado para atender às necessidades do programa de geração e busca num labirinto implementado utilizando-se um grafo
*/
#include <stdio.h>
#include <stdlib.h>
#include "../header/fila.h"
#include "../header/global.h"

/*
Funcao de inicializacao da fila estatica
Parametros:
	fila- fila a ser inicializada
	tam- numero de nos utilizaveis da fila
*/
void fila_init(fila_t *fila, int tam) {
	fila->ini = 0;
	fila->fim = 0;
	fila->tam = tam+1; //Aloca uma posicao a mais que o tamanho para usar como referencia no posicionamento da fila
	fila->fila = (dataF_t *) _malloc(sizeof(dataF_t) * fila->tam);
}

/*
Fucao para adicionar uma nova informaçao a fila
Parametros:
	fila- fila na qual a informaçao sera inserida
	info- informacao a ser inserida

Variaveis:
	pos- posicao do vetor(fila) na qual a informacao sera inserida

Retorno:
	1- fila cheia
	0- informacao inserida com sucesso
*/
int fila_add(fila_t *fila, dataF_t info) {
	int pos;

	pos = (fila->fim+1) % fila->tam; //Passa para a proxima posição da fila, dando a volta no vetor se necessario
	if(pos == fila->ini) { //Se a fila esta cheia, nada e inserido
		return 1;

	} else {
		fila->fila[fila->fim] = info;
		fila->fim = pos;
	}
	return 0;
}

/*
Funcao para remocao de uma informacao da fila
Parametros:
	fila- fila da qual a informacao será inserida
	retorno- variavel na qual a informacao retirada é colocada
*/
void fila_remove(fila_t *fila, dataF_t *retorno) {
	if(fila->ini == fila->fim) { //Caso a fila esteja vazia, é retornado NULL na variável de retorno
		retorno = NULL;
	} else {
		*retorno = fila->fila[fila->ini];
		fila->ini = (fila->ini+1) % fila->tam; //Passa para a proxima posição da fila, dando a volta no vetor se necessario
	}
}

/*
Função de impressão da fila
Parametros:
	fila- fila a ser impressa

Variáveis:
	pos- variável utilizada para percorrer a fila
*/
void fila_print(fila_t *fila) {
	int pos;

	pos = fila->ini;
	while(pos != fila->fim) { //Enquanto o final da fila não é atingido
		printf("%d ", fila->fila[pos]);
		pos = (pos+1) % fila->tam; //Passa para a proxima posição da fila, dando a volta no vetor se necessario

	}
	printf("\n");
}

/*
Função para verificação de fila vazia
Parâmetros:
	fila- fila a ser verificada

Retorno:
	1- fila vazia
	0- fila não vazia
*/
int fila_vazia(fila_t *fila) {
	if(fila->ini == fila->fim) {
		return 1;
	} else {
		return 0;
	}
}

/*
Função para liberação da memória alcada para a fila
Parâmetro:
	fila- fila a ter sua memória desalocada
*/
void fila_destroy(fila_t *fila) {
	if(fila->fila != NULL) {
		free(fila->fila);
	}
}
