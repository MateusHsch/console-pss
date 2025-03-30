#include "../include/csv_parser.h"
#include "../include/queue.h"

Queue* pegaProcess(Queue* q, char *path)
{
    char linha[128];
    Process* p;

    FILE *arq = fopen(path, "r");
    if(arq == NULL){
        perror("Erro ao abrir Process!!!\n");
        return NULL;
    }
    fgets(linha, sizeof(linha), arq);
    while(fgets(linha, sizeof(linha), arq) != NULL){

        p = malloc(sizeof(Process));
        if(!p){
            printf("Process p não foi alocado com sucesso!\n");
            return(NULL);
        }
#ifdef DEBUG_ALOCACOES
        alocado++;
#endif

        char *token = strtok(linha, ",");
        if (!token)
        {
            free(p);
            continue;
        }
        strncpy(p->pid, token, sizeof(p->pid) - 1);
        p->pid[sizeof(p->pid) - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token)
        {
            free(p);
            continue;
        }
        p->t_chegada = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            free(p);
            continue;
        }
        p->prioridade = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
        {
            free(p);
            continue;
        }
        p->instrucoes = atoi(token);

        token = strtok(NULL, "\n");
        if (!token)
        {
            free(p);
            continue;
        }
        p->taxa_io = atof(token);
        
        q = filaAdicionar(q, p);
    }

    fclose(arq);
    return(q);
}