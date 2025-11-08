#include <stdio.h>

#include "../include/process.h"
#include "../include/sjf_sim.h"
#include "../include/rr_sim.h"


#define NUM_PROCS 4
#define QUANTUM 4


int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    int initProcVals[NUM_PROCS][2] = {{0, 8}, {1, 4}, {2, 9}, {3, 5}}; 

    Process processes[NUM_PROCS];
    
    for(int i = 0; i < NUM_PROCS; i++) {
        processes[i] = processInit(initProcVals[i][0], initProcVals[i][1]);
    }

    //sjfSimulate(processes, NUM_PROCS);
    rrSimulate(processes, NUM_PROCS, QUANTUM);


    return 0;
}
