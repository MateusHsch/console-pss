#include "defines.h"
#include "Simulator.hpp"

// argv format: [program_name, scheduling_algorithm, quantum(if needed), core_speed1, ... , processFilePath]
int main(int argc, char *argv[])
{
    // --- Initialization ---

    // Check for minimum arguments
    if ((argc < 4) || (std::string(argv[1]) == "RR" && argc < 5))
    {
        std::cerr << "Usage: " << argv[0] << " <scheduling_algorithm> [quantum_if_RR] <core_speeds...> <process_file_path>" << std::endl;
        return 1;
    }

    // Initialize values

    int quantum = 0;
    int n_cores = argc - 3;
    int idx_cores = 2;
    SchedulingAlgorithm algorithm = SchedulingAlgorithm::FCFS;
    std::string algorithm_string = argv[1];
    std::string process_file_path = argv[argc - 1];

    // Fill values

    if (algorithm_string == "FCFS")
    {
        algorithm = SchedulingAlgorithm::FCFS;
    }
    else if (algorithm_string == "RR")
    {
        quantum = std::stoi(argv[2]);
        if(quantum <= 0) quantum = 1;
        algorithm = SchedulingAlgorithm::RR;
        idx_cores = 3;
        n_cores = argc - 4;
    }
    else if (algorithm_string == "SJF")
    {
        algorithm = SchedulingAlgorithm::SJF;
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

    // Create Simulator

    Simulator simulator(algorithm, quantum, core_speeds);


#ifdef DEBUG_INIT
    std::cout << "\n=======<DEBUG_INIT>======\n";
    std::cout << "Algorithm: " << argv[1] << "\n";
    std::cout << "Quantum: " << quantum << "\n";
    std::cout << "Number of Cores: " << n_cores << "\n";
    std::cout << "=========================" << std::endl;
#endif

    // --- Simulation Loop ---

    bool running = true;
    while(running)
    {
        switch (simulator.get_state())
        {
        case SimulatorState::LOADING:

            simulator.load_processes_from_csv(process_file_path);

            simulator.set_state(SimulatorState::RUNNING);
            break;

        case SimulatorState::RUNNING:

            simulator.run();

            // Check if finished or advance clock if not
            if(simulator.is_finished())
            {
                simulator.set_state(SimulatorState::EXITING);
            }
            else
            {
                simulator.advance_clock();
            }

            break;
        
        case SimulatorState::EXITING:
            
#ifdef TEST_STATISTICS
            simulator.print_results();
#endif
            running = false;
            break;
        
        default:
            break;
        }

#ifdef DEBUG_MAIN_LOOP_STEPS
        std::cout << "Press ENTER to continue...";
        std::getchar();
        std::cout << std::endl;
#endif
    }

    return 0;
}
