#include "Scheduler.hpp"

Scheduler::Scheduler(SchedulingAlgorithm algorithm) : algorithm(algorithm) {}

void Scheduler::add_process(std::shared_ptr<Process> process) {
    process->set_state(ProcessState::READY);

    if(algorithm == SchedulingAlgorithm::SJF)
    {
        // Place the process ordered by remaining_instructions
        for(auto it = ready_processes.begin(); it != ready_processes.end(); )
        {
            if(process->get_remaining_instructions() < (*it)->get_remaining_instructions())
            {
                ready_processes.insert(it, process);
                return;
            }
            it++;
        }
        // If is the last, push back
    }

    ready_processes.push_back(process);
}

void Scheduler::schedule()
{
    // Implement here when needed
}

void Scheduler::add_process_SJF(std::shared_ptr<Process> process) {
    process->set_state(ProcessState::READY);

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
