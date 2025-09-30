#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>

enum Process_States{
    LOADED = 1,
    READY,
    RUNING,
    WAITING,
    TERMINATED,
};

typedef struct process{
    int pid;
    int arrival_time;
    int burst_time; 
    int total_instructions;
    int instructions_remaining;
    float io_rate;                  // frequency of I/O requests
    int io_end_time;                // end time of the I/O operation
    enum Process_States state;                      // loaded, ready, running, waiting, terminated
} Process;

void process_print(Process *process);

#endif