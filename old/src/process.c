#include "../include/process.h"

void process_print(Process *process)
{
    printf("%p: {pid: %d, arrival_time: %d, burst_time: %d, total_inst: %d, inst_remaining: %d, io_rate: %.2f, io_end_time: %d, state: %d}\n"
        ,process
        ,process->pid
        ,process->arrival_time
        ,process->burst_time
        ,process->total_instructions
        ,process->instructions_remaining
        ,process->io_rate
        ,process->io_end_time
        ,process->state);
}