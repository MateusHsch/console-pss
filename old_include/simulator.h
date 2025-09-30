#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "core.h"
#include "process.h"
#include "list.h"

typedef struct simulator {
    int time;
    int scheduling_algorithm;
    int n_cores;
    float quantum;
    Core *cores;
    List *p_ready;
    List *p_waiting;
    List *p_terminated;
} Simulator;

Simulator* simulator_create(int argc, char *argv[]);
void simulator_destroy(Simulator *sim);
void simulator_print(Simulator *sim);

enum Simulator_States{
    BUILD_SIMULATOR = 1,
    LOAD_PROCESSES,
    SCHEDULE_PROCESSES,
    EXIT,
};

enum TipoEscalonamento {
    FCFS = 1,
    SJF,
    RR,
    PS,
    MQS,
};

#endif