#include "Simulator.hpp"

Simulator::Simulator(SchedulingAlgorithm algorithm, int quantum, const std::vector<int> &core_speeds)
    : clock(0)
    , scheduler(algorithm)
    , quantum(quantum)
    , state(SimulatorState::LOADING)
    , engine(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()))
    , dist(0.0f, 1.0f)
{
    for (int i = 0; i < core_speeds.size(); ++i)
    {
        cores.emplace_back(i, core_speeds[i]);
    }
}

void Simulator::load_processes_from_csv(std::string file_path)
{
#ifdef DEBUG_LOAD_CSV
    std::cout << "\n=====<DEBUG_LOAD_CSV>====\n";
    std::cout << "Loading from: " << file_path << "\n";
#endif

    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
    }

    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line)) {

#ifdef DEBUG_LOAD_CSV
        std::cout << "Read line: " << line << "\n";
#endif

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
        arrival_processes.push_back(process);
    }

#ifdef DEBUG_LOAD_CSV
    std::cout << "=========================" << std::endl;
#endif
}

void Simulator::run()
{
            // Handle Arrivals
            handle_arrivals();

            // Handle I/O
            handle_io();

            // Schedule Processes
            schedule_processes();

            // Execute Cores
            execute_cores();

            // Handle exection results
            // - check finished
            // - check I/O goes here
            // - preeption (depends on the algorithm)
            handle_execution_results();

            // Dispatch Processes
            dispatch_processes();

#ifdef DEBUG_PROCESSES_LISTS
            std::cout << "===< Lists Sizes >===" << std::endl;
            std::cout << "Arrival " << get_arrival_processes().size() << "/" << get_all_processes().size() << std::endl;
            std::cout << "Ready " << get_ready_processes().size() << "/" << get_all_processes().size() << std::endl;
            std::cout << "Waiting " << get_waiting_processes().size() << "/" << get_all_processes().size() << std::endl;
            std::cout << "Finished " << get_finished_processes().size() << "/" << get_all_processes().size() << std::endl;
#endif

#ifdef DEBUG_CORES
            std::cout << "===< Cores >===" << std::endl;
            for (auto& core : get_cores())
            {
                std::cout << "Core " << core.get_id() << ": process ";
                if (core.is_busy())
                    std::cout << core.get_current_process()->get_pid() << std::endl;
                else
                    std::cout << "-" << std::endl;
            }
#endif
}

void Simulator::handle_arrivals()
{
    for (auto it = arrival_processes.begin(); it != arrival_processes.end(); )
    {
        if ((*it)->get_arrival_time() <= clock)
        {
            if(scheduler.get_algorithm() == SchedulingAlgorithm::SJF)
            {
                scheduler.add_process_SJF(*it);
            }
            else
            {
                scheduler.add_process(*it);
            }
            it = arrival_processes.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Simulator::handle_io()
{
    // Handle waiting processes list
    for (auto it = waiting_processes.begin(); it != waiting_processes.end(); )
    {
        // If I/O timer ends
        if ((*it)->wait())
        {
            if(scheduler.get_algorithm() == SchedulingAlgorithm::SJF)
            {
                scheduler.add_process_SJF(*it);
            }
            else
            {
                scheduler.add_process(*it);
            }
            it = waiting_processes.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Simulator::schedule_processes()
{
    scheduler.schedule();
}

void Simulator::execute_cores()
{
    for (auto& core : cores)
    {
        if (core.is_busy())
        {
#ifdef DEBUG_CORES
            std::cout << "[" << clock << "]: Process " << core.get_current_process()->get_pid() << " EXECUTED on core " << core.get_id() << std::endl;
#endif
            core.execute();
        }
    }
}

void Simulator::handle_execution_results()
{
    for (auto& core : cores)
    {
        // Skip empty cores
        if (!core.is_busy()) { continue; }

        auto running_process = core.get_current_process();

        // Check finished processes
        if (running_process->is_completed())
        {
#ifdef DEBUG_CORES
            std::cout << "[" << clock << "]: Process " << running_process->get_pid() << " COMPLETED." << std::endl;
#endif
            auto process = core.release_process();
            process->set_completion_time(clock);

            finished_processes.push_back(process);
        }

        // Check I/O passing a random number
        else if (running_process->check_io(dist(engine)))
        {
#ifdef DEBUG_CORES
            std::cout << "[" << clock << "]: Process " << running_process->get_pid() << " BLOCKED" << std::endl;
#endif
            waiting_processes.push_back(core.block_process());
        }

        // Check Preeption RR
        else if ((scheduler.get_algorithm() == SchedulingAlgorithm::RR) && (core.get_process_timer() >= quantum))
        {
#ifdef DEBUG_CORES
            std::cout << "[" << clock << "]: Process " << running_process->get_pid() << " PREEMPTED (Quantum)" << std::endl;
#endif
            auto preepted_process = core.preempt_process();
            scheduler.add_process(preepted_process);
        }

    }
}

void Simulator::dispatch_processes()
{
    for (auto& core : cores)
    {
        if (!core.is_busy() && scheduler.has_ready_process())
        {
            auto process = scheduler.get_next_process();

            if(process->is_first_run())
            {
                process->set_first_run_time(clock);
            }

            core.assign_process(process);
#ifdef DEBUG_CORES
            std::cout << "[" << clock << "]: Process " << process->get_pid() << " ASSIGNED to core " << core.get_id() << std::endl;
#endif
        }
    }
}

bool Simulator::is_finished() const
{
    return finished_processes.size() == all_processes.size();
}

void Simulator::print_results()
{
    // Print Header
    std::cout << "\n===< PROCESSES >" << std::string(100, '=') << std::endl;
    std::cout << std::left 
              << std::setw(6) << "PID" 
              << std::setw(18) << "Name" 
              << std::setw(10) << "Arrival"
              << std::setw(16) << "Completion"
              << std::setw(16) << "CPU Bursts"
              << std::setw(18) << "Turnaround Time"
              << std::setw(16) << "Waiting Time"
              << std::setw(16) << "Response Time"
              << std::endl;
    std::cout << std::string(116, '-') << std::endl;

    for(auto& process : finished_processes)
    {
        process->print_result();
    }
    std::cout << std::string(116, '-') << std::endl;

    std::cout << "\n===< CORES >" << std::string(104, '=') << std::endl;
    std::cout << std::left 
              << std::setw(6) << "CORE"
              << std::setw(12) << "Speed"
              << std::setw(18) << "Context Switches"
              << std::setw(12) << "Busy Time"
              << std::setw(12) << "Idle Time"
              << std::setw(14) << "Utilization"
              << std::endl;
    std::cout << std::string(116, '-') << std::endl;

    for(auto& core : cores)
    {
        core.print_result(clock); // Passing total simulation time
    }
    std::cout << std::string(116, '-') << std::endl;
}