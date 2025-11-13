#include "Core.hpp"

Core::Core(int id, int speed)
    : id(id)
    , speed(speed)
{
    process_timer = 0;
    context_switches = 0;
    busy_time = 0;
    current_process = nullptr;
};

void Core::execute()
{
    current_process->run(speed);
    process_timer++;
    busy_time++;
}

void Core::assign_process(std::shared_ptr<Process> process)
{
    current_process = process;
    process->set_state(ProcessState::RUNNING);
    process_timer = 0;
}

std::shared_ptr<Process> Core::release_process()
{
    auto process = current_process;
    if (process) {
        process->set_state(ProcessState::TERMINATED);
    }
    current_process = nullptr;
    return process;
}

std::shared_ptr<Process> Core::block_process()
{
    auto process = current_process;
    if (process) {
        process->set_state(ProcessState::WAITING);
        context_switches++;
    }
    current_process = nullptr;
    return process;
}

std::shared_ptr<Process> Core::preempt_process()
{
    auto process = current_process;
    if (process) {
        process->set_state(ProcessState::READY);
        context_switches++;
    }
    current_process = nullptr;
    return process;
}


void Core::print_info() const {
    std::cout << "===< Core " << id << " >===\n"
              << "Speed (MIPS): " << speed << "\n"
              << "Current Process ID: " << (current_process ? std::to_string(current_process->get_pid()) : "None") << "\n"
              << "=================\n";
}

void Core::print_result(int total_sim_time) const
{
    int idle_time = total_sim_time - busy_time;
    double utilization = (total_sim_time > 0) ?
                            (static_cast<double>(busy_time) / static_cast<double>(total_sim_time)) * 100.0 :
                            0.0;

    std::cout << std::left
                << std::setw(6) << id
                << std::setw(12) << speed
                << std::setw(18) << context_switches
                << std::setw(12) << busy_time
                << std::setw(12) << idle_time
                << std::fixed << std::setprecision(2) << utilization << "%"
                << std::endl;
}