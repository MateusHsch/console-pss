#include "Core.hpp"

Core::Core(int id, int speed)
    : id(id)
    , speed(speed)
{
    current_process = nullptr;
};

void Core::execute()
{
    //Method implementation
}

void Core::assign_process(std::shared_ptr<Process> process)
{
    current_process = process;
    process->set_state(ProcessState::RUNNING);
}

//TODO Check this method
std::shared_ptr<Process> Core::release_process()
{
    auto process = current_process;
    if (process) {
        process->set_state(ProcessState::TERMINATED);
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