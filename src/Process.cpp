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
    , completion_time(-1)
    , first_run_time(-1)
    , cpu_bursts_count(0)
    , io_bursts_count(0)
{};

void Process::run(int instructions)
{
    cpu_bursts_count++;

    remaining_instructions -= instructions;
    if (remaining_instructions < 0) { remaining_instructions = 0; }
}

bool Process::check_io(float rand)
{
    if(rand <= io_rate)
    {
        //TODO: Maybe change to a random number of cycles
        block(5);
        state = ProcessState::WAITING;

        return true;
    }

    return false;
}

void Process::block(int duration)
{
    io_timer = duration;
}

bool Process::wait()
{
    io_bursts_count++;

    if(--io_timer <= 0)
        return true;
    else
        return false;
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

void Process::print_result() const
{
    int turnaround_time = completion_time - arrival_time;
    int waiting_time = turnaround_time - cpu_bursts_count;
    int response_time = first_run_time - arrival_time;

    std::cout   << std::left
                << std::setw(6) << pid
                << std::setw(18) << name
                << std::setw(10) << arrival_time
                << std::setw(16) << completion_time
                << std::setw(16) << cpu_bursts_count
                << std::setw(18) << turnaround_time
                << std::setw(16) << waiting_time
                << std::setw(16) << response_time
                << std::endl;
}