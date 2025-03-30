#ifndef UTILS_H
#define UTILS_H

// Estrutura de um nó da fila
typedef struct node
{
  void *item;
  struct node *next;
  struct node *prev;
} Node;

// Estrutura da lista
typedef struct list
{
  int size;
  Node *start;
  Node *end;
} List;

List *listCreate();
void listDelete(List *q);
List *listAddStart(List *q, void *item);
List *listAddEnd(List *q, void *item);
void *listRemoveFirst(List *q);
void *listRemoveLast(List *q);
void listPrint(List *list);

#endif