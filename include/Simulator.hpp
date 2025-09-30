#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "defines.h"
#include "Scheduler.hpp"
#include "Core.hpp"
#include "Process.hpp"
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <list>

enum class SimulatorState {
    INITIALIZING,
    RUNNING,
    EXITING
};

class Simulator {
public:
    Simulator(std::unique_ptr<Scheduler> scheduler, const std::vector<int> &core_speeds);

    // --- Methods ---

    /**
     * @brief Load processes from a CSV file
     */
    void load_processes_from_csv(std::string file_path);

    /**
     * @brief Run the entire simulation until all processes are terminated
     */
    void run();

    /**
     * @brief Handle the arrival of new processes at the current clock time
     */
    void handle_arrivals();

    /**
     * @brief Handle I/O operations
     */
    void handle_io();

    /**
     * @brief Execute all cores for one time unit
     */
    void execute_cores();

    /**
     * @brief Dispatch processes to available cores
     */
    void dispatch_processes();

    /**
     * @brief Check if all processes have been completed
     * @return true if all processes are finished, false otherwise
     */
    bool is_finished() const;

#ifdef DEBUG_LOADED_PROCESSES
    /**
     * @brief Print all loaded processes for debugging
     */
    void print_loaded_processes() const;
#endif

    // --- Getters and Setters ---

    int get_clock() const { return clock; }
    SimulatorState get_state() const { return state; }

    void set_state(SimulatorState new_state) { state = new_state; }

private:
    // --- Attributes ---

    int clock; // Simulation clock in time units
    SimulatorState state;
    std::unique_ptr<Scheduler> scheduler;
    std::vector<Core> cores;
    std::vector<std::shared_ptr<Process>> all_processes;
    std::list<std::shared_ptr<Process>> arrival_queue;
    std::list<std::shared_ptr<Process>> waiting_processes;
    std::list<std::shared_ptr<Process>> finished_processes;
};

#endif // SIMULATOR_H