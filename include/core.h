#ifndef CORE_H
#define CORE_H

#include "process.h"

typedef struct {
    int id;
    int mips;       // speed in millions of instructions per second
    Process *current_process;
    int busy_until; // for time tracking
} Core;

#endif