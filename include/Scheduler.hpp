#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.hpp"

#include <memory>
#include <queue>

class Scheduler {
public:
    Scheduler() = default;
    virtual ~Scheduler() = default;

    // --- Interface ---

    //TODO: CHECK this method
    virtual void schedule() = 0;

    /**
     * @brief Add a process to the scheduler's ready queue
     * @param process Shared pointer to the process to be added
     */
    void add_process(std::shared_ptr<Process> process);

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

protected:
    std::deque<std::shared_ptr<Process>> ready_processes;
};

class FCFS_Scheduler : public Scheduler {
public:
    FCFS_Scheduler() = default;

    /**
     * @brief Implement the FCFS scheduling logic
     */
    void schedule() override;
};

class RR_Scheduler : public Scheduler {
public:
    RR_Scheduler(int quantum) : quantum(quantum) {}
    
    /**
     * @brief Implement the Round Robin scheduling logic
     */
    void schedule() override;

private:
    int quantum; // Time slice for Round Robin
};

#endif // SCHEDULER_H