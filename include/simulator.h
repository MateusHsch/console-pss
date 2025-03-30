#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "scheduler.h"
#include "core.h"
#include "list.h"


typedef struct {
    int time;
    int scheduling_algorithm;
    int n_cores;
    float quantum;
    Core *cores;
    List *p_ready;
    List *p_waiting;
} Simulator;

Simulator* simulator_create(int argc, char *argv[]);
void simulator_destroy(Simulator *sim);

#endif