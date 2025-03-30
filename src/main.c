// Include Section //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/simulator.h"
#include "../include/defines.h"
#include "../include/list.h"
#include "../include/process.h"


// Global Data //

#ifdef DEBUG_ALOCATION
int alocated_bytes = 0;
int dealocated_bytes = 0;
#endif

enum Simulator_States{
    BUILD_SIMULATOR = 1,
    LOAD_PROCESSES,
    SCHEDULE,
    EXIT,
};


// Main Program

// argv format: [program_name, scheduling_algorithm, quantum(if needed), core_speed1, ... , processFilePath]
int main(int argc, char *argv[])
{
    int simulator_state = BUILD_SIMULATOR;

    while (1)
    {
        switch (simulator_state)
        {
        case BUILD_SIMULATOR:
            
            Simulator *sim = simulator_create(argc, argv);

            simulator_state = LOAD_PROCESSES;
            break;
        
        case LOAD_PROCESSES:
            
            Process *process;

            for(int i=0; i<5; i++)
            {
                process = (Process*) malloc(sizeof(Process));
#ifdef DEBUG_ALOCATION
                alocated_bytes += sizeof(Process);
#endif
                if(!process)
                    exit(1);
                process->pid = i;
                process->arrival_time = 1+i;
                process->total_instructions = 100+i;
                process->instructions_remaining = 0.0;
                process->instructions_remaining = 10-i;
                process->state = 0;
                sim->p_ready = list_add_end(sim->p_ready, process);
            }

            list_print(sim->p_ready);
            list_print(sim->p_waiting);
            printf("\n");

            process = list_remove_fist(sim->p_ready);
            sim->p_waiting = list_add_end(sim->p_waiting, process);
            list_print(sim->p_ready);
            list_print(sim->p_waiting);
            printf("\n");

            process = list_remove_fist(sim->p_ready);
            sim->p_waiting = list_add_end(sim->p_waiting, process);
            list_print(sim->p_ready);
            list_print(sim->p_waiting);

            printf("\n\n");
            list_print_processes(sim->p_ready);
            list_print_processes(sim->p_waiting);

            // load_process_from_csv(p_loaded);
        
            simulator_state = EXIT;
            break;

        // EXIT
        default:
            
            simulator_destroy(sim);

#ifdef DEBUG_ALOCATION
            printf("==============================\n");
            printf("bytes alocated:   %d\n", alocated_bytes);
            printf("bytes dealocated: %d\n", dealocated_bytes);
            printf("==============================\n");
#endif

            return 0;
        }
    }

    return 0;
}
