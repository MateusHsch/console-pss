#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "defines.h"
#include "list.h"
#include "simulator.h"
#include "core.h"

List* load_ready_processes(int time, List *p_ready, List *p_loaded);
void execute_cores(Simulator *sim, double tick_duration_sec);
int ocupied_cores(Simulator *sim);
//void io_operations(Simulator *sim);
List* check_waiting_processes(Simulator *sim);
void schedule_FCFS(Simulator *sim);

#endif