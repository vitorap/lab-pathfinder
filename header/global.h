/*

	Vitor Albuquerque de Paula 			(8628220)
*/


#include <stdio.h>

#ifndef GLOBAL_H_
#define GLOBAL_H_

void *_malloc(unsigned int size); //Encapsulamento do malloc com a verificação de sucesso na alocaçao
void *_calloc(unsigned int size, unsigned int times); //Encapsulamento do calloc com averificação de sucesso na alocaçao

#endif
