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
        perror("List malloc returned NULL!!!\n");
        exit(1);
    }
#ifdef DEBUG_ALOCATION
    alocated_bytes += sizeof(List);
#endif
#ifdef LOG_ADRESS_ALOCATION   
        printf("malloc of List: {%p}\n", list);
#endif

    list->size = 0;
    list->start = NULL;
    list->end = NULL;

    return list;
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
            if(this->process)
            {
#ifdef LOG_ADRESS_DEALOCATION   
                printf("free of Process: {%p}\n", this->process);
#endif
                free(this->process);
#ifdef DEBUG_ALOCATION
                dealocated_bytes += sizeof(Process);
#endif
            }
            
#ifdef LOG_ADRESS_DEALOCATION   
            printf("free of Node: {%p}\n", this);
#endif
            free(this);
#ifdef DEBUG_ALOCATION
            dealocated_bytes += sizeof(Node);
#endif
            this = next;
        }

        list->size = 0;     

#ifdef LOG_ADRESS_DEALOCATION   
        printf("free of List: {%p}\n", list);
#endif
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
        perror("Node malloc returned NULL!!!\n");
        exit(1);
    }
#ifdef DEBUG_ALOCATION
    alocated_bytes += sizeof(Node);
#endif
#ifdef LOG_ADRESS_ALOCATION   
        printf("malloc of Node: {%p}\n", this);
#endif

    this->process = process;
    list->size++;

    this->prev = list->end;
    this->next = NULL;

    if (list->end)
        list->end->next = this;
    else
        list->start = this;

    list->end = this;

    return list;
}

Process *list_remove_first(List *list)
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
    else
        list->end = NULL;

#ifdef LOG_ADRESS_DEALOCATION   
    printf("free of Node: {%p}\n", this);
#endif
    free(this);
#ifdef DEBUG_ALOCATION
    dealocated_bytes += sizeof(Node);
#endif

    return process;
}

Process *list_remove_by_process(List *list, Process *process)
{
    if (!list)
        return NULL;

    if (!list->start)
        return NULL;

    Node *this = list->start;

    while (this)
    {
        if(this->process == process)
            break;
        else
            this = this->next;
    }

    if(!this)
        return NULL;
    
    if (this == list->start)
    {
        list->start = this->next;
        if(list->start)
            list->start->prev = NULL;
        else
            list->end = NULL;
    }
    else if (this == list->end)
    {
        list->end = this->prev;
        if(list->end)
            list->end->next = NULL;
        else
            list->start = NULL;
    }
    else
    {
        this->next->prev = this->prev;
        this->prev->next = this->next;
    }

    list->size--;
    
#ifdef LOG_ADRESS_DEALOCATION   
    printf("free of Node: {%p}\n", this);
#endif
    free(this);
#ifdef DEBUG_ALOCATION
    dealocated_bytes += sizeof(Node);
#endif

    return process;
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
        printf("List size: %d\n", list->size);
        printf("start\n");
        printf("|\n");
        while(this)
        {
            process_print(this->process);
            printf("|\n");
            this = this->next;
        }
        printf("end\n");
    }
}
