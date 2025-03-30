#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "process.h"

// Estrutura de um nó da fila
typedef struct node{
    Process *process;
    struct node *next;
    struct node *prev;
}Node;

// Estrutura da fila
typedef struct list{
    int size;
    Node *start;
    Node *end;
}List;

List* list_create();
void list_destroy(List *list);
List* list_add_end(List *list, Process *process);
Process* list_remove_fist(List *list);
void list_print(List *list);
void list_print_processes(List *list);

#endif