#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/process_queue.h"
#include "../include/schedule_display.h"
#include "../include/sjf_sim.h"


#define TIME_STEP 1
#define NUM_PROCS 4
#define OUTPUT_SIZE_INIT 50

#define PROC_RES_LBL "\n\nFinal Scheduling Results:\n\n"

void processPrintBodyTab(Process* p) {
    processPrintBody(p, (LINE_START "\t")); // Print process
}


Process** sjfSimulate(Process procs[], int numProcs, int* totalTime) {
    // Declare array to hold results
    size_t resultsSize = OUTPUT_SIZE_INIT;
    Process** results = malloc(resultsSize* sizeof(Process*));
    

    // Ensure process array is sorted by arrival time
    processSortArrival(procs, numProcs);

    int time = 0;
    Process* currentExec = NULL; // Currently executing process
    ProcessQueue* readyQueue = processQueueInit(numProcs); // Queue of executing processes
    int nextProc = 0; // Next process to arrive

    // Loop until no process execution, no queued CPU bursts, and no pending arrivals
    while(nextProc < numProcs || currentExec || processQueueSize(readyQueue)) {
        /*printf(TIME_HEADER, time); // Print time unit header
        
        if(currentExec) // Print currently executing process
            execProcessPrint(currentExec);

        // Print ready queue in order of remaining CPU time
        printf(READY_QUEUE_HEADER);
        processPrintHeader((LINE_START "\t"));
        processQueueMap(readyQueue, processPrintBodyTab);
*/
        // Update wait and turnaround time for processes in ready queue:
        processQueueMap(readyQueue, processWait);

        if(currentExec) // Update currently executing process 
            processExec(currentExec, TIME_STEP, time);

        if(currentExec && currentExec->remainingTime == 0) // Process completed execution
            currentExec = NULL;
/*
        if(nextProc < numProcs && procs[nextProc].arrivalTime == time) {
            printf(ARRIVE_HEADER);
            processPrintHeader(LINE_START "\t");
        }
*/
        // Handle arriving processes
        while(nextProc < numProcs && procs[nextProc].arrivalTime == time) {
            processPrintBody(&procs[nextProc], (LINE_START "\t"));
            processQueuePush(readyQueue, &procs[nextProc++]);
        }

        // Preemptively update currently executing process
        if(currentExec) processQueuePush(readyQueue, currentExec);
        currentExec = processQueuePop(readyQueue);


        results[time] = currentExec;
        time += TIME_STEP; // Increment time
    }

    *totalTime = time;
    return results;
}


