#include "Simulator.hpp"

Simulator::Simulator(std::unique_ptr<Scheduler> scheduler, const std::vector<int> &core_speeds)
    : clock(0), scheduler(std::move(scheduler))
    , state(SimulatorState::INITIALIZING)
{
    for (int i = 0; i < core_speeds.size(); ++i)
    {
        cores.emplace_back(i, core_speeds[i]);
    }
}

void Simulator::load_processes_from_csv(std::string file_path)
{
    std::cout << "Loading processes from: " << file_path << std::endl;

    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
    }

    std::string line;
    std::getline(file, line); // Skip header line

    while(std::getline(file, line)) {
        std::cout << "Read line: " << line << std::endl;

        std::istringstream ss(line);
        std::string token;

        int pid;
        std::string name;
        int arrival_time;
        int total_instructions;
        float io_rate;

        std::getline(ss, token, ',');
        pid = std::stoi(token);

        std::getline(ss, token, ',');
        name = token;

        std::getline(ss, token, ',');
        arrival_time = std::stoi(token);

        std::getline(ss, token, ',');
        total_instructions = std::stoi(token);

        std::getline(ss, token, ',');
        io_rate = std::stof(token);

        std::shared_ptr<Process> process = std::make_shared<Process>(pid, name, arrival_time, total_instructions, io_rate);
        all_processes.push_back(process);
        arrival_queue.push_back(process);
    }
}

void Simulator::run()
{
    //TODO: Check if I will do it here
}

void Simulator::handle_arrivals()
{
    // Implementation for handling process arrivals
}

void Simulator::handle_io()
{
    // Implementation for handling I/O operations
}

void Simulator::execute_cores()
{
    // Implementation for executing all cores for one time unit
}

void Simulator::dispatch_processes()
{
    // Implementation for dispatching processes to available cores
}

bool Simulator::is_finished() const
{
    return finished_processes.size() == all_processes.size();
}

#ifdef DEBUG_LOADED_PROCESSES
void Simulator::print_loaded_processes() const
{
    for(const auto& process : all_processes) {
        process->print_info();
    }
}
#endif