/*

	Vitor Albuquerque de Paula 			(8628220)
*/


#include <stdio.h>
#include <stdlib.h>
#include "../header/global.h"

/*
Função que encapsula a função malloc e sua verificação de sucesso
Parametro:
	size- tamanho da memória a ser alocada

Retorno:
	ptr- ponteiro para void com a memória alocada em caso de sucesso (caso o processo falhe o programa é terminado com úma saída negativa (-1))
*/
void *_malloc(unsigned int size) {
	void *ptr;

	ptr = malloc(size);
	if(ptr == NULL) {
		printf("Erro na alocacao de memoria\n");
		exit(-1);
	}
	return ptr;
}

/*
Função que encapsula a função calloc e sua verificação de sucesso
Parametros:
	size- tamanho da memória a ser alocada pelo tipo de dado
	times- numero de posiçoes do dado desejadas

Retorno:
	ptr- ponteiro para void com a memória alocada em caso de sucesso (caso o processo falhe o programa é terminado com úma saída negativa (-1))
*/
void *_calloc(unsigned int size, unsigned int times) {
	void *ptr;

	ptr = calloc(size, times);
	if(ptr == NULL) {
		printf("Erro na alocacao de memoria\n");
		exit(-1);
	}
	return ptr;
}
