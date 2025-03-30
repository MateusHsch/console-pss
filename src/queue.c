
#include <stdlib.h>
#include "queue.h"

/**
 * @brief Aloca e inicializa a estrutura que controla uma fila de processos.
 * 
 * @return Ponteiro para a fila.
 */
Queue* filaCriar()
{
    Queue *q = (Queue*) malloc(sizeof(Queue));
    if (q){
#ifdef DEBUG_ALOCACOES
        alocado++;
#endif
        q->tamanho = 0;
        q->inicio = NULL;
        q->fim = NULL;
    }else{
        printf("Queue não foi alocado com sucesso!\n");
    }
    return q;
}

/**
 * @brief Desaloca a fila e todos os seus elementos.
 * 
 * @param q Ponteiro para a fila.
 */
void filaDestruir(Queue *q)
{
    if(q){
        Node *atual = q->inicio;
        Node *prox;
        while (atual){
            prox = atual->prox;
            if(atual->processo)
            {
                free(atual->processo);
#ifdef DEBUG_ALOCACOES
                desalocado++;
#endif
            }
            free(atual);
#ifdef DEBUG_ALOCACOES
            desalocado++;
#endif
            atual = prox;
        }
        free(q);
#ifdef DEBUG_ALOCACOES
        desalocado++;
#endif
    }
}

/**
 * @brief Aloca e adiciona um processo na fila.
 * 
 * @param q Ponteiro para a fila.
 * @param p Processo a ser adicionado na fila.
 * 
 * @return Ponteiro para a fila alterada.
 */
Queue* filaAdicionar(Queue *q, Process *p)
{
    if(q){
        Node *novo = malloc(sizeof(Node));
        if (!novo){
            printf("Novo Node não foi alocado com sucesso!\n");
            return(NULL);
        }
#ifdef DEBUG_ALOCACOES
        alocado++;
#endif
        q->tamanho++;
        
        novo->processo = p;
        novo->prox = NULL;
        if(q->fim){
            q->fim->prox = novo;
            q->fim = novo;
        }else{
            q->inicio = novo;
            q->fim = novo;
        }
    }
    return q;
}

/**
 * @brief Remove o primeiro elemento da fila de processos.
 * 
 * @param q Ponteiro para a fila.
 * 
 * @return Primeiro processo da fila.
 */
Process* filaRemover(Queue *q)
{
    if(q->inicio)
    {
        Node *atual = q->inicio;
        Process* p;
        q->tamanho--;
        p = atual->processo;
        q->inicio = atual->prox;
#ifdef DEBUG_ALOCACOES
        desalocado++;
#endif
        free(atual);
        return(p);
    }
    return(NULL);
}
Process* filaRemoverPos(Queue *q, int idx)
{
    if(q->inicio)
    {
        Node* atual = q->inicio;
        while(idx)
        {
            atual = atual->prox;
            idx--;
        }
        Process* p = atual->processo;
        if (atual->ante)
        {
            atual->ante->prox = atual->prox;
        }else{
            q->inicio = atual->prox;
        }
        if (atual->prox)
        {
            atual->prox->ante = atual->ante;
        }else{
            q->fim = atual->ante;
        }
        free(atual);
#ifdef DEBUG_ALOCACOES
        desalocado++;
#endif
        return(p);
    }
    return(NULL);
}

/**
 * @brief Imprime a fila de processos.
 * 
 * @param q Ponteiro para a fila.
 */
void filaImprimir(Queue *q)
{
    if(q){
        Node *atual = q->inicio;
        printf("q -> ");
        while(atual){
            printf("{%p} <-> ", atual);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

/**
 * @brief imprime a fila de processos com os detalhes de cada processo.
 * 
 * @param q Ponteiro para a fila.
 */
void filaProcessosImprimir(Queue *q)
{
    if(q){
        Node *atual = q->inicio;
        printf("q\n");
        printf("|\n");
        while(atual){
            printf("{%p}  ->  pid: %s   t_chegada: %d  instrucoes: %d  taxa_io: %.2f\n", atual, atual->processo->pid, atual->processo->arrival_time, atual->processo->total_instructions, atual->processo->io_rate);
            printf("|\n");
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}
