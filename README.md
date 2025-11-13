# Console Process Scheduler Simulator

The console-pss implemets the First Come First Served, Round Robin and Shortest Job First algorithm. It is a upgrade of a old school project made in Java, after in C and now in C++.
Also, each process has an I/O rate to simulate I/O operations and block processes.
(The C implementation can still be found in the folder /old).

## Algorithms

A quick explaination about each scheduling algorithm.

### First Come First Served (FCFS)

This is the simplest algorithm, the processes are placed in the ready queue in the same order they arrive. Therefore, the first process that comes is the first to be served. This implementation use an I/O rate to simulate I/O operations. Thus, a process that is assigned to a core can be realeased before completion, since it can be blocked.

### Round Robin (RR)

In this algorithm, the arrival works just like FCFS. The diference is, this algorithm preempt a process running in a core after a certain amount of time (quantum), when this happens the process is placed back to the end of the ready queue. This algorithm try to be more fair with processes, giving the same amount of execution time for every process, but this method can highly increase the context switches as we use smaller quantums.

### Shortest Job First (SJF)

This algorithm is similar to FCFS, but now the processes are placed in the ready queue, ordered by burst time (remaining instructions in this implementation). When a process is placed in a core it will run until completion or perform I/O.

## Compile

This program was compiled using GCC 6.3.0.

`g++ -Iinclude src/*.cpp -o console-pss`

## Run

The program require the simulator parameters to run, the format is:
`<program> <scheduling_algorithm> [quantum_if_RR] <core_speeds...> <process_file_path>` 

There is a example using FCFS, 3 cores, the speeds are 100, 200 and 300 (instructions or MI per clock):
`.\console-pss FCFS 100 200 300 samples/10_processes.csv`

Example for RR:
`.\console-pss RR 3 100 200 300 samples/10_processes.csv`
