#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    int arrival_time;
    int total_instructions;
    float io_rate;  // frequency of I/O requests
    int instructions_remaining;
    int state;      // ready, running, waiting, terminated
    // other metrics you want to track
} Process;

enum Process_States{
    LOADED = 0,
    READY,
    RUNING,
    WAITING,
    TERMINATED,
};

#endif