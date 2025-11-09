#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/process.h"
#include "../include/sjf_sim.h"
#include "../include/rr_sim.h"
#include "../include/schedule_display.h"


#define NUM_PROCS 4
#define QUANTUMS {4, 6, 8, 2}
#define NUM_QUANTUMS 4
#define NUM_SIMS (NUM_QUANTUMS + 1)


int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    int initProcVals[NUM_PROCS][2] = {{0, 8}, {1, 4}, {2, 9}, {3, 5}}; 
    Process processes[NUM_PROCS];
    
    for(int i = 0; i < NUM_PROCS; i++) {
        processes[i] = processInit(initProcVals[i][0], initProcVals[i][1]);
    }

    const int rrQuantums[] = QUANTUMS;

    Process*** results = malloc(NUM_SIMS * sizeof(Process**));
    int resultSizes[NUM_QUANTUMS] = {0};
    //sjfSimulate(processes, NUM_PROCS);

    for(int i = 0; i < NUM_QUANTUMS; i++) { // Run RR sims
        // Create copy of processes to account for in-place modification
        Process procsCopy[NUM_PROCS];
        memcpy(procsCopy, processes, sizeof(processes));

        results[i] = rrSimulate(procsCopy, NUM_PROCS, rrQuantums[i], &resultSizes[i]);
        printf("\n\n\n\n\n BMark w/ QUANTUM = %d completed\n", rrQuantums[i]);
    }

    execProcessTable(results, resultSizes, NUM_QUANTUMS); // Display results

    // Free results memory
    for(int i = 0; i < NUM_SIMS; i++) {
        if(results[i]) // Free each row
            free(results[i]);
    }

    free(results); // Free outer array


    return 0;
}
