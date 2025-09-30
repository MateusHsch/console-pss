#include "../include/csv_parser.h"

#ifdef DEBUG_ALOCATION
extern int alocated_bytes;
extern int dealocated_bytes;
#endif

List* load_process_from_csv(List *list, char* path)
{
    if(path == NULL)
    {
        perror("NULL file path provided!!!\n");
        return NULL;
    }

    FILE *file = fopen(path, "r");
    if(!file){
        perror("Could not open the given file!!!\n");
        return NULL;
    }

    char line[128];
    int line_idx = 1;
    int fail_counter = 0;
    Process *process;
    char *token;

    printf("\n========< CSV_PARSER >========\n");
    printf("Loading processes from:\n%s\n", path);
    printf("==============================\n");

    // Gets the .cvs header
    fgets(line, sizeof(line), file);
    while(fgets(line, sizeof(line), file))
    {
        line_idx++;
        if (line[0] == '\n')
            continue;

        process = (Process*) malloc(sizeof(Process));
        if(!process)
        {
            perror("Process malloc returned NULL!!!\n");
            exit(1);
        }
#ifdef DEBUG_ALOCATION
        alocated_bytes += sizeof(Process);
#endif
#ifdef LOG_ADRESS_ALOCATION   
        printf("malloc of Process: {%p}\n", process);
#endif
        // Get process PID
        token = strtok(line, ",");
        if(!token)
        {
            printf("line %d: Could not acquire process pid...\n", line_idx);
            fail_counter++;
            parser_free_process(process);
            continue;
        }
        process->pid = atoi(token);

        // Get process Arrival time
        token = strtok(NULL, ",");
        if(!token)
        {
            printf("line %d: Could not acquire process arrival time...\n", line_idx);
            fail_counter++;
            parser_free_process(process);
            continue;
        }
        process->arrival_time = atoi(token);

        // Get process Total instructions
        token = strtok(NULL, ",");
        if(!token)
        {
            printf("line %d: Could not acquire process total instructions...\n", line_idx);
            fail_counter++;
            parser_free_process(process);
            continue;
        }
        process->total_instructions = atoi(token);

        // Get process IO rate
        token = strtok(NULL, "\n");
        if(!token)
        {
            printf("line %d: Could not acquire process io rate...\n", line_idx);
            fail_counter++;
            parser_free_process(process);
            continue;
        }
        process->io_rate = atof(token);

        process->burst_time = 0;
        process->instructions_remaining = process->total_instructions;
        process->io_end_time = 0;
        process->state = LOADED;

        printf("line %d -> PID: %d, Arrival time: %d, Total intructions: %d, IO rate: %.2f\n"
                ,line_idx
                ,process->pid
                ,process->arrival_time
                ,process->total_instructions
                ,process->io_rate);
        list = list_add_end(list, process);
    }
    printf("==============================\n");
    if(fail_counter)
        printf("%d processes could not been acquired...\n", fail_counter);
    else
        printf("All processes have been sucefully acquired...\n");
    printf("==============================\n");

    fclose(file);
    return(list);
}

void parser_free_process(Process *process)
{
#ifdef LOG_ADRESS_DEALOCATION   
    printf("free of Process: {%p}\n", process);
#endif
    free(process);
#ifdef DEBUG_ALOCATION
    dealocated_bytes += sizeof(Process);
#endif
}
