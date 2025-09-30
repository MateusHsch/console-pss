// Include Section //
#include "defines.h"
#include "Simulator.hpp"


// argv format: [program_name, scheduling_algorithm, quantum(if needed), core_speed1, ... , processFilePath]
int main(int argc, char *argv[])
{
    // --- Initialization ---

    // Check for minimum arguments
    if (argc < 4){
        std::cerr << "Usage: " << argv[0] << " <scheduling_algorithm> [quantum_if_RR] <core_speeds...> <process_file_path>" << std::endl;
        return 1;
    }

    // Get the scheduling_algorithm
    int quantum = 1;
    int n_cores = 1;
    int idx_cores = 2;
    std::unique_ptr<Scheduler> scheduler;
    std::string algorithm_string = argv[1];
    std::string process_file_path = argv[argc - 1];

    if (algorithm_string == "FCFS")
        scheduler = std::make_unique<FCFS_Scheduler>();
    else if (algorithm_string == "RR")
    {
        quantum = std::stoi(argv[2]);
        scheduler = std::make_unique<RR_Scheduler>(quantum);
        idx_cores = 3;
        n_cores = argc - 4;
    }
    else
    {
        std::cerr << "Error: Invalid algorithm choice." << std::endl;
        return 1;
    }

    std::vector<int> core_speeds(n_cores);
    for (int i = 0; i < n_cores; ++i) {
        core_speeds[i] = atoi(argv[idx_cores + i]);
    }

#ifdef DEBUG_INIT
    std::cout << "\n=======<DEBUG_INIT>======\n";
    std::cout << "Algorithm: " << argv[1] << std::endl;
    std::cout << "Quantum: " << quantum << std::endl;
    std::cout << "Number of Cores: " << n_cores << std::endl;
    std::cout << "=========================\n";
#endif

    // Create Simulator instance

    Simulator simulator(std::move(scheduler), core_speeds);
    std::cout << "Simulator state: " << static_cast<int>(simulator.get_state()) << std::endl;

    // --- Simulation Loop ---

    bool running = true;
    while(running)
    {
        switch (simulator.get_state())
        {
        case SimulatorState::INITIALIZING:
            simulator.load_processes_from_csv(process_file_path);

#ifdef DEBUG_LOADED_PROCESSES
            simulator.print_loaded_processes();
#endif
            running = false;
            //simulator.set_state(SimulatorState::RUNNING);
            break;

        case SimulatorState::RUNNING:
            /* code */
            break;
        
        case SimulatorState::EXITING:
            /* code */
            break;
        
        default:
            break;
        }

        //running = !simulator.is_finished();
    }

    return 0;
}
