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
#include <iomanip>
#include <chrono>

enum class SimulatorState {
    LOADING,
    RUNNING,
    EXITING
};

class Simulator {
public:
    Simulator(SchedulingAlgorithm algorithm, int quantum, const std::vector<int> &core_speeds);

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
     * @brief Schedule processes using the scheduler
     */
    void schedule_processes();

    /**
     * @brief Dispatch processes to available cores
     */
    void dispatch_processes();

    /**
     * @brief Execute all cores for one time unit
     */
    void execute_cores();

    /**
     * 
     */
    void handle_execution_results();

    /**
     * @brief Check if all processes have been completed
     * @return true if all processes are finished, false otherwise
     */
    bool is_finished() const;

    /**
     * @brief Advance the simulation clock by one time unit
     */
    void advance_clock() { clock++; }

    void print_results();

    // --- Getters and Setters ---

    int get_clock() const { return clock; }
    SimulatorState get_state() const { return state; }
    //SchedulingAlgorithm get_algorithm() const { return scheduler.get_algorithm(); };

    void set_state(SimulatorState new_state) { state = new_state; }

#ifdef DEBUG_PROCESSES_LISTS
    std::deque<std::shared_ptr<Process>> get_ready_processes() const { return scheduler.get_ready_processes(); }
    std::vector<std::shared_ptr<Process>> get_all_processes() const { return all_processes; }
    std::list<std::shared_ptr<Process>> get_arrival_processes() const { return arrival_processes; }
    std::list<std::shared_ptr<Process>> get_waiting_processes() const { return waiting_processes; }
    std::list<std::shared_ptr<Process>> get_finished_processes() const { return finished_processes; }
#endif
#ifdef DEBUG_CORES
    std::vector<Core> get_cores() const { return cores;}
#endif

private:
    // --- Attributes ---

    int clock; // Simulation clock in time units
    int quantum;
    SimulatorState state;
    Scheduler scheduler;
    std::vector<Core> cores;
    std::vector<std::shared_ptr<Process>> all_processes;
    std::list<std::shared_ptr<Process>> arrival_processes;
    std::list<std::shared_ptr<Process>> waiting_processes;
    std::list<std::shared_ptr<Process>> finished_processes;

    // --- Atributos para Geração de Números Aleatórios ---
    std::mt19937 engine;
    std::uniform_real_distribution<float> dist;
};

#endif // SIMULATOR_H