#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>

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

    //TODO: Revisar unidade de tempo (clocks, ms, s) 
    /**
     * @brief Simulate blocking the process for I/O for a given duration
     * @param duration Duration to block in time units
     */
    void block(int duration);

    /**
     * @brief Ticks down the I/O timer
     */
    void wait();

    /**
     * @brief Check if the process has completed its execution
     * @return true if the process has no remaining instructions, false otherwise
     */
    bool is_completed() const { return remaining_instructions <= 0; }

    /**
     * @brief Print process information
     */
    void print_info() const;

    // --- Getters and Setters ---

    int get_pid() const { return pid; }
    const std::string& get_name() const { return name; }
    ProcessState get_state() const { return state; }

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

    int cpu_bursts_count;
    int io_bursts_count;
};

#endif // PROCESS_H