// Include Section //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/simulator.h"
#include "../include/defines.h"
#include "../include/process.h"
#include "../include/list.h"
#include "../include/csv_parser.h"


// Global Data //

#ifdef DEBUG_ALOCATION
int alocated_bytes = 0;
int dealocated_bytes = 0;
#endif


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
            
            List *p_loaded = list_create();

            p_loaded = load_process_from_csv(p_loaded, argv[argc-1]);
            
            simulator_state = SCHEDULE;
            break;

        case SCHEDULE:

            simulator_state = EXIT;
            break;

        // EXIT
        default:
            
            list_destroy(p_loaded);

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
