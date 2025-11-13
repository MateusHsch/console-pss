#ifndef PROCESS_H
#define PROCESS_H

#include "defines.h"
#include <string>
#include <iostream>
#include <random>
#include <iomanip>

enum class ProcessState {
    LOADED,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class Process {
public:
    Process(int pid, const std::string& name, int arrival_time, int total_instructions, float io_rate);

    // --- Methods ---

    /**
     * @brief Simulate running the process for a given number of instructions
     * @param instructions Number of instructions to run in MIPS
     */
    void run(int instructions);

    bool check_io(float rand);

    /**
     * @brief Starts the I/O timer
     * @param duration Duration to block in time units
     */
    void block(int duration);

    /**
     * @brief Decrease the I/O timer by one time unit
     * @return true if the I/O is complete and the process can move to READY, false otherwise
     */
    bool wait();

    /**
     * @brief Check if the process has completed its execution
     * @return true if the process has no remaining instructions, false otherwise
     */
    bool is_completed() const { return remaining_instructions <= 0; }

    bool is_first_run() const { return first_run_time == -1; }

    void set_first_run_time(int clock) { first_run_time = clock; }

    void set_completion_time(int clock) { completion_time = clock; }

    /**
     * @brief Print process information
     */
    void print_info() const;

    void print_result() const;

    // --- Getters and Setters ---

    int get_pid() const { return pid; }
    const std::string& get_name() const { return name; }
    ProcessState get_state() const { return state; }
    int get_arrival_time() const { return arrival_time; }
    int get_remaining_instructions() const { return remaining_instructions; }
    float get_io_rate() const { return io_rate; }

    void set_state(ProcessState new_state) { state = new_state; }

private:
    // --- Core Attributes ---
    
    int pid;
    std::string name;
    ProcessState state;
    
    // --- Timing & Execution Attributes ---

    int arrival_time;
    int total_instructions;
    int remaining_instructions;
    float io_rate; // Probability of performing I/O (0.0 to 1.0)
    int io_timer; // Timer for how long it remains in the WAITING state

    // --- Statistics (Tracked during simulation) ---

    int completion_time;
    int first_run_time;
    int cpu_bursts_count;
    int io_bursts_count;
};

#endif // PROCESS_H