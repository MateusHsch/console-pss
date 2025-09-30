#include "Scheduler.hpp"

void Scheduler::add_process(std::shared_ptr<Process> process) {
    ready_processes.push_back(process);
}

std::shared_ptr<Process> Scheduler::get_next_process() {
    if (ready_processes.empty()) {
        return nullptr;
    }
    auto process = ready_processes.front();
    ready_processes.pop_front();
    return process;
}

bool Scheduler::has_ready_process() const {
    return !ready_processes.empty();
}

// --- FCFS Scheduler Implementation ---

void FCFS_Scheduler::schedule() {
    // FCFS scheduling logic can be implemented here if needed
}

// --- RR Scheduler Implementation ---

void RR_Scheduler::schedule() {
    // Round Robin scheduling logic can be implemented here if needed
}

