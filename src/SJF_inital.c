#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/process.h"
#include "../include/process_queue.h"


#define TIME_STEP 1
#define NUM_PROCS 4

#define PROC_RES_LBL "\n\nFinal Scheduling Results:\n\n"


void srtfSimulate(Process procs[], int numProcs) {
    int time = 0;
    Process* currentExec = NULL; // Currently executing process
    ProcessQueue* readyQueue = processQueueInit(numProcs); // Queue of executing processes
    int nextProc = 0; // Next process to arrive

    // Loop until no process execution, no queued CPU bursts, and no pending arrivals
    while(nextProc < numProcs || currentExec || processQueueSize(readyQueue)) {
        // Update wait and turnaround time for processes in ready queue:
        processQueueMap(readyQueue, processWait);

        if(currentExec) { // Update currently executing process 
            //printf("\nCurrent Executing Process Present\n"); // DEBUG *******
            printf("\nProcess [%d] Executing\n", currentExec->processId);
            processExec(currentExec, TIME_STEP, time);
        }

        if(currentExec && currentExec->remainingTime == 0) // Process completed execution
            currentExec = NULL;

        if(nextProc < numProcs && procs[nextProc].arrivalTime == time) {
            printf("+------------------------------------------------------------------------------------+\n");
            printf("| Arriving Processes:                                                                |\n");
        }

        // Handle arriving processes
        while(nextProc < numProcs && procs[nextProc].arrivalTime == time) {
            processPrint(&procs[nextProc]);
            processQueuePush(readyQueue, &procs[nextProc++]);
        }

        // Preemptively update currently executing process
        if(currentExec) processQueuePush(readyQueue, currentExec);
        currentExec = processQueuePop(readyQueue);

        time += TIME_STEP; // Increment time
    }


}


int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    int initProcVals[NUM_PROCS][2] = {{0, 8}, {1, 4}, {2, 9}, {3, 5}}; 

    Process processes[NUM_PROCS];
    
    for(int i = 0; i < NUM_PROCS; i++) {
        processes[i] = processInit(initProcVals[i][0], initProcVals[i][1]);
        processPrint(&processes[i]); // DEBUG *******
    }


    srtfSimulate(processes, NUM_PROCS);

    printf(PROC_RES_LBL);

    for(int i = 0; i < NUM_PROCS; i++)
        processPrint(&processes[i]);

    //printProcesses(processes, NUM_PROCS);

    return 0;
}
