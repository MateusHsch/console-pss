#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

// Estrutura de um nó da fila
typedef struct node{
    Process *processo;
    struct node *prox;
    struct node *ante;
}Node;

// Estrutura da fila
typedef struct queue{
    int tamanho;
    Node *inicio;
    Node *fim;
}Queue;

Queue* queue_create();
void queue_destroy(Queue *q);
Queue* queue_add(Queue *q, Process *p);
Process* queue_remove(Queue *q);
void queue_print(Queue *q);
void queue_print_processes(Queue *q);

#endif