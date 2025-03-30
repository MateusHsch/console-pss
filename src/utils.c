#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

List *listCreate()
{
  List *list = (List *)malloc(sizeof(List));
  if (list)
  {

    list->size = 0;
    list->start = NULL;
    list->end = NULL;
  }
  else
  {
    printf("Fail on malloc List!\n");
  }
  return list;
}

void listDelete(List *list)
{
  if (list)
  {
    Node *this = list->start;
    Node *next;
    while (this)
    {
      next = this->next;
      if (this->item)
      {
        free(this->item);

      }
      free(this);

      this = next;
    }
    free(list);

  }
}

List *listAddStart(List *list, void *item)
{
  if (!list)
    return (NULL);
  if (!item)
    return (NULL);

  Node *new = malloc(sizeof(Node));
  if (!new)
  {
    printf("Fail on malloc Node!\n");
    return (NULL);
  }

  list->size++;
  new->item = item;
  new->prev = NULL;
  if (list->start)
  {
    list->start->prev = new;
    new->next = list->start;
    list->start = new;
  }
  else
  {
    list->start = new;
    list->end = new;
    new->next = NULL;
  }
  return list;
}

List *listAddEnd(List *list, void *item)
{
  if (!list)
    return (NULL);
  if (!item)
    return (NULL);

  Node *new = malloc(sizeof(Node));
  if (!new)
  {
    printf("Fail on malloc Node!\n");
    return (NULL);
  }

  list->size++;
  new->item = item;
  new->next = NULL;
  if (list->end)
  {
    list->end->next = new;
    new->prev = list->end;
    list->end = new;
  }
  else
  {
    list->start = new;
    list->end = new;
    new->prev = NULL;
  }
  return list;
}

void *listRemoveFirst(List *list)
{
  if (!list)
    return NULL;
  if (!list->start)
    return NULL;

  Node *this = list->start;
  void *item;
  list->size--;
  item = this->item;
  list->start = this->next;
  list->start->prev = NULL;
  free(this);

  return (item);
}

void *listRemoveLast(List *list)
{
  if (!list)
    return NULL;
  if (!list->end)
    return NULL;

  Node *this = list->end;
  void *item;
  list->size--;
  item = this->item;
  list->end = this->prev;
  list->end->next = NULL;
  free(this);

  return (item);
}

void listPrint(List *list)
{
  if (list)
  {
    Node *this = list->start;
    printf("size: %d\n", list->size);
    printf("start - ");
    while (this)
    {
      printf("{%p} - ", this->item);
      this = this->next;
    }
    printf("end\n");
  }
  else
  {
    printf("NULL\n");
  }
}
