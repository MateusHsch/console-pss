
#include "../include/simulator.h"


// Global Data Section //

#ifdef DEBUG_ALOCATION
extern int alocated_bytes;
extern int dealocated_bytes;
#endif


// Implementation Section //

Simulator* simulator_create(int argc, char *argv[])
{
    // argv format: [program_name, scheduling_algorithm, quantum(if needed), core_speed1, ... , processFilePath]
    if (argc < 4){
        printf("More arguments were expected!!!\n");
        exit(1);
    }

    Simulator* sim = (Simulator*) malloc(sizeof(Simulator));
    if(!sim)
    {
        printf("simulator malloc returned NULL!!!\n");
        exit(1);
    }
#ifdef DEBUG_ALOCATION
    alocated_bytes += sizeof(Simulator);
#endif

    int scheduling_algorithm = FCFS;
    float quantum = 1.0;
    int idx_cores = 2;
    int n_cores = 1;
    Core *cores;
    List *p_ready;
    List *p_waiting;

    // Get the scheduling_algorithm
    if (!strcmp(argv[1], "FCFS"))
        scheduling_algorithm = FCFS;
    if (!strcmp(argv[1], "SJF"))
        scheduling_algorithm = SJF;
    if (!strcmp(argv[1], "RR"))
        scheduling_algorithm = RR;

    // Get quantum and define position os cores
    if(scheduling_algorithm == RR)
    {
        quantum = atof(argv[2]);
        idx_cores = 3;
        n_cores = argc - 4;
    }
    else
    {
        idx_cores = 2;
        n_cores = argc - 3;
    }
    
    // Get cores
    cores = (Core*) malloc(n_cores * sizeof(Core));
    if(!cores)
    {
        printf("cores malloc returned NULL!!!\n");
        exit(1);
    }
#ifdef DEBUG_ALOCATION
    alocated_bytes += n_cores * sizeof(Core);
#endif

    for(int i=0; i<n_cores; i++)
    {
        cores[i].id = i;
        cores[i].mips = atoi(argv[idx_cores + i]);
        cores[i].current_process = NULL;
        cores[i].busy_until = 0;
    }

    // Build simulator
    sim->scheduling_algorithm = scheduling_algorithm;
    sim->quantum = quantum;
    sim->n_cores = n_cores;
    sim->cores = cores;
    sim->time = 0;
    sim->p_ready = list_create();
    sim->p_waiting = list_create();

    return(sim);
}

void simulator_destroy(Simulator *sim)
{
    free(sim->cores);
#ifdef DEBUG_ALOCATION
    dealocated_bytes += sim->n_cores * sizeof(Core);
#endif

    if(sim->p_ready)
        list_destroy(sim->p_ready);
    
    if(sim->p_waiting)
        list_destroy(sim->p_waiting);

    free(sim);
#ifdef DEBUG_ALOCATION
    dealocated_bytes += sizeof(Simulator);
#endif
}

