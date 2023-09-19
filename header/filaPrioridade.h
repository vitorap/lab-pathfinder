#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include <stdlib.h>
#include "listOrd.h"

// Você pode incluir os tipos necessários para dataLO_t se estiverem em um arquivo diferente.
// #include "seu_arquivo_de_tipos.h"

typedef struct {
    dataLO_t *dados; // Ponteiro para o array que armazena os elementos
    float *prioridades; // Ponteiro para o array que armazena as prioridades
    int capacidade; // Capacidade máxima da fila
    int tamanho; // Tamanho atual da fila
} priorityQueue_t;

void priorityQueue_init(priorityQueue_t *queue, int capacidade);
int priorityQueue_empty(priorityQueue_t *queue);
void priorityQueue_push(priorityQueue_t *queue, dataLO_t data, float prioridade);
void priorityQueue_pop(priorityQueue_t *queue, dataLO_t *data);
void priorityQueue_destroy(priorityQueue_t *queue);

#endif // FILA_PRIORIDADE_H
