#include "../include/scheduler.h"

#ifdef DEBUG_ALOCATION
extern int alocated_bytes;
extern int dealocated_bytes;
#endif

List* load_ready_processes(int time, List *p_ready, List *p_loaded)
{
    // Protection
    if(!p_loaded)
        return(NULL);
    
    Node *this = p_loaded->start;
    Process *process;

    // Add arrived processes in p_ready
    while (this)
    {
        Node *next = this->next; // save next before doing anything

        if (this->process->arrival_time <= time)
        {
            process = list_remove_by_process(p_loaded, this->process);
            process->state = READY;
            p_ready = list_add_end(p_ready, process);
        }

        this = next; // move to next
    }

    return(p_ready);
}

void execute_cores(Simulator *sim, double tick_duration_sec)
{
#ifdef LOG_EXECUTE_CORES
    printf("\n=======< EXECUTE_CORES >======\n");
#endif
    for(int i=0; i<sim->n_cores; i++)
    {
#ifdef LOG_EXECUTE_CORES
        printf("CORE %d\n", sim->cores[i].id);
#endif
        if(sim->cores[i].current_process)
        {
            Process *process = sim->cores[i].current_process;
            //process_print(process);

            // Check IO exceptions
            float rand_rate = (float) rand() / (float) RAND_MAX;
            if(rand_rate <= process->io_rate)
            {
#ifdef LOG_EXECUTE_CORES
                printf("{%p} performed IO.\n", process);
                printf("==============================\n");
#endif
                if (process->total_instructions > 10000000)
                    process->io_end_time = sim->time + 10; // heavier processes
                else
                    process->io_end_time = sim->time + 5;  // lighter processes
                
                process->state = WAITING;
                sim->p_waiting = list_add_end(sim->p_waiting, process);
                sim->cores[i].current_process = NULL;
                continue; // move to next core
            }

            // Decrease executed instructions
            int instructions_executed = sim->cores[i].mips * 1000000 * tick_duration_sec;

            if (process->instructions_remaining > instructions_executed)
            {
                process->instructions_remaining -= instructions_executed;
            }
            else
            {
                process->instructions_remaining = 0;
            }
#ifdef LOG_EXECUTE_CORES
            printf("{%p} executed instructions.\n", process);
#endif

            // Check if the process terminates
            if(process->instructions_remaining == 0)
            {
#ifdef LOG_EXECUTE_CORES
                printf("{%p} finished execution.\n", process);
#endif
                process->burst_time = sim->time - process->arrival_time;
                process->state = TERMINATED;
                sim->p_terminated = list_add_end(sim->p_terminated, process);

                sim->cores[i].current_process = NULL;
            }
        }
#ifdef LOG_EXECUTE_CORES
        printf("==============================\n");
#endif
    }
}

int ocupied_cores(Simulator *sim)
{
    int ocupied = 0;

    for(int i=0; i<sim->n_cores; i++)
    {
        if(sim->cores[i].current_process)
            ocupied++;
    }

    return ocupied;
}

/*
void io_operations(Simulator *sim)
{
    float rand_rate;

    for(int i=0; i<sim->n_cores; i++)
    {
        if(sim->cores[i].current_process)
        {
            rand_rate = (float) rand() / (float) RAND_MAX;
            if(rand_rate <= sim->cores[i].current_process->io_rate)
            {
                printf("{%p} realizou IO!!!\n", sim->cores[i].current_process);
                sim->cores[i].current_process->state = WAITING;
                sim->p_waiting = list_add_end(sim->p_waiting, sim->cores[i].current_process);
                sim->cores[i].current_process = NULL;
            }
        }
    }
}
*/

List* check_waiting_processes(Simulator *sim)
{
    if(!sim->p_waiting)
        return sim->p_ready;

    Node *this = sim->p_waiting->start;

    while (this)
    {
        Node *next = this->next;

        if (sim->time >= this->process->io_end_time)
        {
            this->process->state = READY;
            Process *process = list_remove_by_process(sim->p_waiting, this->process);
            sim->p_ready = list_add_end(sim->p_ready, process);
        }

        this = next;
    }
    return sim->p_ready;
}

void schedule_FCFS(Simulator *sim)
{
    Process *process;

    for(int i=0; i<sim->n_cores; i++)
    {
        if(!sim->cores[i].current_process)
        {
            process = list_remove_first(sim->p_ready);
            
            if(process)
            {
                // Get the first ready process
                sim->cores[i].current_process = process;
                // Set the busy until time
                sim->cores[i].busy_until = sim->time + (int) ceil(sim->cores[i].current_process->instructions_remaining / sim->cores[i].mips);
                // Set the state
                sim->cores[i].current_process->state = RUNING;
            }
        }
    }
}
