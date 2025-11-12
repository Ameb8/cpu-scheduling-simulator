
#include <stdio.h>
#include <stdlib.h>

#include "../include/process.h"
#include "../include/process_dequeue.h"

#include "../include/rr_sim.h"

#define OUTPUT_SIZE_INIT 50

Process** rrSimulate(Process proc[], int numProcs, int quantum, int* totalTime) {
    int time = 0; // Tracks time from epoch
    int execTime = 0; // Tracks time process spent executing since switch
    int procIdx = 0; // Index of next arriving process
    
    // Declare array to hold results
    size_t resultsSize = OUTPUT_SIZE_INIT; 
    Process** results = calloc(resultsSize, sizeof(Process*));

    ProcessDequeue* readyQueue = processDequeueInit(); // Queue of ready processes
    Process* currentExec = NULL; // Currently executing process

    // Loop by 1 time unit until all process complete execution
    while(procIdx < numProcs || processDequeueSize(readyQueue) > 0 || currentExec) {
        // Append arriving processes to queue
        while(procIdx < numProcs && proc[procIdx].arrivalTime == time)
            processDequeueAppend(readyQueue, &proc[procIdx++]);

        // Process finished execution
        if(currentExec && currentExec->remainingTime == 0) {
            execTime = 0;
            currentExec = NULL;
        }
        
        // Preemptively switch executing process
        if(execTime >= quantum) {
            processDequeueAppend(readyQueue,  currentExec);
            currentExec = NULL;
            execTime = 0;
        }

        if(!currentExec) // Select next process to execute
            currentExec = processDequeuePoll(readyQueue);

        if(currentExec) { // Update process metrics
            processExec(currentExec, 1, time); // Update executing process
            execTime++;
        }

        // Increase results array if necessary
        if(time >= resultsSize)
            growProcessArr(&results, resultsSize, resultsSize * 2);
        
        // Write to results
        results[time] = currentExec;

        processDequeueMap(readyQueue, processWait); // Update waiting processes
    
        //if(currentExec)
            //printf("\n\n At time %d:\t\tPROC[%d]", time, currentExec->processId);
        //printf("\t\tWAIT[%zu]", processDequeueSize(readyQueue));

        time++; // Move time forward
    }

    processDequeueFree(readyQueue);
    *totalTime = time;
    return results;
}
