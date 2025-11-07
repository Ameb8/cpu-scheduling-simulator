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
        // Label Box with time
        //printf("\n+--------------------------------------------------------------------------------+\n");
        //printf("|                                  Time = %-4d                                  |\n", time);
        
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
            //printf("\nArriving process at index %d\n", procs[nextProc].processId); // DEBUG *******
            
            processPrint(&procs[nextProc]);
            processQueuePush(readyQueue, &procs[nextProc++]);
        }

        // Preemptively update currently executing process
        if(currentExec) processQueuePush(readyQueue, currentExec);
        currentExec = processQueuePop(readyQueue);

        /*
        Process* nextExec = processQueuePop(readyQueue);

        if(!currentExec) {
            currentExec = nextExec;
        } else if(nextExec->remainingTime < currentExec->remainingTime) {
            processQueuePush(readyQueue, currentExec);
            currentExec = processQueuePop(readyQueue);
        }*/
/*
        // Display current scheduling state
        if(currentExec)
            printf(
                "\nTime: %d\tCurrently Executing: %d\tRemaining Time: %d\tBurst Time: %d",
                time,
                currentExec->processId,
                currentExec->remainingTime,
                currentExec->burstTime
            );
        else
            printf("\nTime: %d\tNo Processes Currently Executing", time);
*/
        time += TIME_STEP; // Increment time
        if(time > 50) break;
    }


}









// Function to perform the SRTF scheduling
// Assumes proc is ordered by arrival time
void srtf(Process procs[], int numProcs) {
    int time = 0;
    Process* currentExec = NULL; // Currently executing process
    ProcessQueue* readyQueue = processQueueInit(numProcs); // Queue of executing processes
    int nextProc = 0; // Next process to arrive

    printf("\nProcess Q created\n"); // DEBUG *******
    
    // Loop until no process execution, no queued CPU bursts, and no pending arrivals
    while(nextProc < numProcs || currentExec || processQueueSize(readyQueue)) {
        // Label Box with time
        printf("\n+--------------------------------------------------------------------------------+\n");
        printf("|                                  Time = %-4d                                  |\n", time);

        if(currentExec) { // Update currently executing process 
            printf("\nCurrent Executing Process Present\n"); // DEBUG *******
            processPrint(currentExec);
            processExec(currentExec, TIME_STEP, time);

        }

        if(currentExec && currentExec->remainingTime == 0) // Process completed execution
            currentExec = NULL;

        // Set next executing process 
        if(!currentExec && processQueueSize(readyQueue) > 0) {
            //printf("\nUpdating current executing process\n"); // DEBUG *******

            currentExec = processQueuePop(readyQueue);
            processResumeExec(currentExec, time);
        }

        if(nextProc < numProcs && procs[nextProc].arrivalTime == time) {
            printf("+--------------------------------------------------------------------------------+\n");
            printf("| Arriving Processes:                                                            |\n");
        }

        // Handle arriving processes
        while(nextProc < numProcs && procs[nextProc].arrivalTime == time) {
            //printf("\nArriving process at index %d\n", procs[nextProc].processId); // DEBUG *******
            
            processPrint(&procs[nextProc]);


            procs[nextProc].lastAck = time; // Update lastAck to process arrival time

            if(!currentExec) { // Set new arrival for execution
                currentExec = &procs[nextProc];
            // Replace current executing process with new arrival   
            } else if(procs[nextProc].burstTime < currentExec->remainingTime) {
                processQueuePush(readyQueue, currentExec); // Move currently executing process to ready queue
                currentExec = &procs[nextProc]; // Update currently executing process
            } else { // Add new process to ready queue
                processQueuePush(readyQueue, &procs[nextProc]);
            }

            nextProc++; // Move index to next arriving process
        }
/*
        // Display current scheduling state
        if(currentExec)
            printf(
                "\nTime: %d\tCurrently Executing: %d\tRemaining Time: %d\tBurst Time: %d",
                time,
                currentExec->processId,
                currentExec->remainingTime,
                currentExec->burstTime
            );
        else
            printf("\nTime: %d\tNo Processes Currently Executing", time);
*/
        time += TIME_STEP; // Increment time
    }
}

// Function to print the processes and their details
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].processId, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].waitingTime, proc[i].turnaroundTime);
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
