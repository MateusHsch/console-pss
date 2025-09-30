// Include Section //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/simulator.h"
#include "../include/defines.h"
#include "../include/process.h"
#include "../include/list.h"
#include "../include/csv_parser.h"
#include "../include/scheduler.h"


// Global Data //

#ifdef DEBUG_ALOCATION
int alocated_bytes = 0;
int dealocated_bytes = 0;
#endif


// Main Program

// argv format: [program_name, scheduling_algorithm, quantum(if needed), core_speed1, ... , processFilePath]
int main(int argc, char *argv[])
{
    // Generates the random seed
    srand(time(NULL));
    // Initializes the machine state
    int simulator_state = BUILD_SIMULATOR;
    // Initialize the running flag
    int running = TRUE;
    // Set the tick duration
    double tick_duration_sec = 0.01; // 10 ms per simulator tick

    Simulator *sim;
    List *p_loaded;

    while (running)
    {
        switch (simulator_state)
        {
        case BUILD_SIMULATOR:
        {
            sim = simulator_create(argc, argv);
            simulator_print(sim);

            simulator_state = LOAD_PROCESSES;
            break;
        }

        case LOAD_PROCESSES:
        {    
            p_loaded = list_create();

            p_loaded = load_process_from_csv(p_loaded, argv[argc-1]);
            
            simulator_state = SCHEDULE_PROCESSES;
            break;
        }

        case SCHEDULE_PROCESSES:
        {
#ifdef DEBUG_PRINT_PROCESSES_LISTS
            printf("\n=====< PROCESSES_LISTS >======\n");
            printf("LOADED_PROCESSES\n");
            list_print(p_loaded);
            printf("==============================\n");
            printf("READY_PROCESSES\n");
            list_print(sim->p_ready);
            printf("==============================\n");
            printf("WAITING_PROCESSES\n");
            list_print(sim->p_waiting);
            printf("==============================\n");
            printf("TERMINATED_PROCESSES\n");
            list_print(sim->p_terminated);
            printf("==============================\n");
#endif

#ifdef DEBUG_PRINT_CORES
            printf("\n==========< CORES >===========\n");
            for(int i=0; i<sim->n_cores; i++)
            {
                printf("CORE %d\n", sim->cores[i].id);
                printf("process: {%p}\n", sim->cores[i].current_process); 
                printf("mips: %d\n", sim->cores[i].mips); 
                printf("==============================\n");
            }
#endif

            sim->p_ready = load_ready_processes(sim->time, sim->p_ready, p_loaded);

            execute_cores(sim, tick_duration_sec);

            sim->p_ready = check_waiting_processes(sim);

            switch (sim->scheduling_algorithm)
            {
            case FCFS:
            {
                /* code */
                schedule_FCFS(sim);

                break;
            }
            case SJF:
            {
                /* code */
                break;
            }
            case RR:
            {
                /* code */
                break;
            }
            case PS:
            {
                /* code */
                break;
            }
            case MQS:
            {
                /* code */
                break;
            }
            default:
            {
                break;
            }
            }

            if( !p_loaded->size &&
                !sim->p_ready->size &&
                !sim->p_waiting->size &&
                !ocupied_cores(sim))

                simulator_state = EXIT;
            else
                sim->time++;
            
            break;
        }

        // EXIT
        default:
        {
#ifdef DEBUG_PRINT_PROCESSES_LISTS
            printf("\n===< TERMINATED_PROCESSES >===\n");
            list_print_processes(sim->p_terminated);
            printf("==============================\n");
#endif

            list_destroy(p_loaded);

            simulator_destroy(sim);

#ifdef DEBUG_ALOCATION
            printf("\n=======<DEBUG_ALOCATION>======\n");
            printf("bytes alocated:   %d\n", alocated_bytes);
            printf("bytes dealocated: %d\n", dealocated_bytes);
            printf("==============================\n");
#endif
            // wait user to end
            printf("\nPress any key to end...\n");
            getchar();

            // End main loop
            running = FALSE;
        }
        }
    }

    return 0;
}
