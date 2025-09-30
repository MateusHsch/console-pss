#ifndef CORE_H
#define CORE_H

#include "Process.hpp"

#include <memory>
#include <iostream>

class Core {
public:
    Core(int id, int speed);

    // --- Methods ---

    /**
     * @brief Simulate executing the current process for one time unit
     */
    void execute();

    /**
     * @brief Assign a process to the core
     * @param process Shared pointer to the process to assign
     */
    void assign_process(std::shared_ptr<Process> process);

    /**
     * @brief Release the current process from the core
     * @return Shared pointer to the released process
     */
    std::shared_ptr<Process> release_process();

    /**
     * @brief Check if the core is busy
     * @return true if the core is busy, false otherwise
     */
    bool is_busy() const {return current_process != nullptr; };
    
    /**
     * @brief Print core information
     */
    void print_info() const;

    // --- Getters and Setters ---

    int get_id() const { return id; }
    int get_speed() const { return speed; }
    std::shared_ptr<Process> get_current_process() const { return current_process; }

private:
    // --- Attributes ---

    int id;
    int speed; // Speed of the core in MIPS
    std::shared_ptr<Process> current_process;
};

#endif // CORE_H