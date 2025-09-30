#include "Process.hpp"

Process::Process(int pid, const std::string& name, int arrival_time, int total_instructions, float io_rate)
    : pid(pid)
    , name(name)
    , state(ProcessState::LOADED)
    , arrival_time(arrival_time)
    , total_instructions(total_instructions)
    , remaining_instructions(total_instructions)
    , io_rate(io_rate)
    , io_timer(0)
    , cpu_bursts_count(0)
    , io_bursts_count(0)
{};

void Process::run(int instructions)
{
    //Method implementation
}

void Process::block(int duration)
{
    //Method implementation
}

void Process::wait()
{
    //Method implementation
}

void Process::print_info() const
{
    std::cout << "===< PID: " << pid << " >===\n"
                << "Name: " << name << "\n"
                << "State: " << static_cast<int>(state) << "\n"
                << "Arrival Time: " << arrival_time << "\n"
                << "Total Instructions: " << total_instructions << "\n"
                << "Remaining Instructions: " << remaining_instructions << "\n"
                << "I/O Rate: " << io_rate << "\n"
                << "I/O Timer: " << io_timer << "\n"
                << "CPU Bursts Count: " << cpu_bursts_count << "\n"
                << "I/O Bursts Count: " << io_bursts_count << "\n"
                << "=================\n";
}