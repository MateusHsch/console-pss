#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "defines.h"
#include "Process.hpp"

#include <memory>
#include <queue>

enum class SchedulingAlgorithm {
    FCFS,
    RR,
    SJF
};

class Scheduler {
public:
    Scheduler(SchedulingAlgorithm algorithm);

    // --- Interface ---

    //TODO: CHECK this method
    void schedule();

    /**
     * @brief Add a process to the scheduler's ready queue changing its state to READY
     * @param process Shared pointer to the process to be added
     */
    void add_process(std::shared_ptr<Process> process);

    void add_process_SJF(std::shared_ptr<Process> process);

    /**
     * @brief Get the next process to be scheduled
     * @return Shared pointer to the next process
     */
    std::shared_ptr<Process> get_next_process();

    /**
     * @brief Check if there are any processes ready to be scheduled
     * @return true if there are ready processes, false otherwise
     */
    bool has_ready_process() const;

    SchedulingAlgorithm get_algorithm() const { return algorithm; }

#ifdef DEBUG_PROCESSES_LISTS
    std::deque<std::shared_ptr<Process>> get_ready_processes() const { return ready_processes;}
#endif

private:
    std::deque<std::shared_ptr<Process>> ready_processes;
    SchedulingAlgorithm algorithm;
};

#endif // SCHEDULER_H