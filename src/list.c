#include "../include/list.h"

// Global Data Section //

#ifdef DEBUG_ALOCATION
extern int alocated_bytes;
extern int dealocated_bytes;
#endif

// Implementation Section //

List *list_create()
{
    List *list = (List *)malloc(sizeof(List));
    if (!list)
    {
        printf("List malloc returned NULL!!!\n");
        exit(1);
    }
#ifdef DEBUG_ALOCATION
    alocated_bytes += sizeof(List);
#endif

    list->size = 0;
    list->start = NULL;
    list->end = NULL;

    return (list);
}

void list_destroy(List *list)
{
    if (list)
    {
        Node *this = list->start;
        Node *next = NULL;
        while (this)
        {
            next = this->next;
            free(this->process);
            free(this);
#ifdef DEBUG_ALOCATION
            dealocated_bytes += sizeof(Process);
            dealocated_bytes += sizeof(Node);
#endif
            this = next;
        }

        free(list);
#ifdef DEBUG_ALOCATION
        dealocated_bytes += sizeof(List);
#endif
    }
}

List *list_add_end(List *list, Process *process)
{
    if (!list)
        return NULL;

    Node *this = (Node *)malloc(sizeof(Node));
    if (!this)
    {
        printf("Node malloc returned NULL!!!\n");
        exit(1);
    }
#ifdef DEBUG_ALOCATION
    alocated_bytes += sizeof(Node);
#endif

    this->process = process;
    list->size++;

    if (list->end)
    {
        list->end->next = this;
        this->prev = list->end;
        this->next = NULL;
        list->end = this;
    }
    else
    {
        list->start = this;
        list->end = this;
        this->prev = NULL;
        this->next = NULL;
    }

    return (list);
}

Process *list_remove_fist(List *list)
{
    if (!list)
        return NULL;

    if (!list->start)
        return NULL;

    Process *process = list->start->process;
    list->size--;

    Node *this = list->start;
    list->start = this->next;

    if (list->start)
        list->start->prev = NULL;

    free(this);
#ifdef DEBUG_ALOCATION
    dealocated_bytes += sizeof(Node);
#endif

    return (process);
}

void list_print(List *list)
{
    if (list)
    {
        Node *this = list->start;
        printf("List size: %d\n", list->size);
        printf("start -> ");
        while (this)
        {
            if (this->next)
                printf("{%p} <-> ", this);
            else
                printf("{%p} ", this);
            this = this->next;
        }
        printf("<- end\n");
    }
}

void list_print_processes(List *list)
{
    if (list)
    {
        Node *this = list->start;
        printf("start\n");
        printf("|\n");
        while(this)
        {
            printf("{%p} -> %p: {pid: %d, arrival_time: %d, total_instructions: %d, io_rate: %.2f, instructions_remaining: %d, state: %d}\n"
                    ,this
                    ,this->process
                    ,this->process->pid
                    ,this->process->arrival_time
                    ,this->process->total_instructions
                    ,this->process->io_rate
                    ,this->process->instructions_remaining
                    ,this->process->state);
            printf("|\n");
            this = this->next;
        }
        printf("end\n");
    }
}
