#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/defines.h"
#include "../include/scheduler.h"
#include "../include/core.h"


typedef struct {
    int time;
    int scheduling_algorithm;
    int n_cores;
    float quantum;
    Core *cores;
    // Queue *p_pronto;
    // Queue *p_espera;
} Simulator;

Simulator* simulator_create(int argc, char *argv[]);
void simulator_destroy(Simulator *sim);

#endif