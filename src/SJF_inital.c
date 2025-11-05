#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/process.h"
#include "../include/process_queue.h"


# define TIME_STEP


int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    return;
}

// Function to perform the SRTF scheduling
// Assumes proc is ordered by arrival time
void srtf(Process procs[], int numProcs) {
    int time = 0;
    Process* currentExec = NULL; // Currently executing process
    ProcessQueue* readyQueue = proccessQueueInit(numProcs); // Queue of executing processes
    int nextProc = 0; // Next process to arrive
    
    // Loop until no process execution or queued CPU bursts
    while(currentExec || procQueueSize(procQueue)) {
        if(currentExec) // Update currently executing process
            processExec(currentExec, TIME_STEP, time);
        
        if(currentExec && currentExec->remainingTime == 0) // Process completed execution
            currentExec = NULL;

        // Set next executing process 
        if(!currentExec && processQueueSize(readyQueue) > 0) {
            currentExec = processQueuePop(readyQueue);
            processResumeExec(currentExec, time);
        }

        // Handle arriving processes
        while(nextProc < numProcs && procs[nextProc]->arrivalTime == time) {
            // Replace current executing process with new arrival
            if(procs[nextProc]->burstTime < currentExec->remainingTime) {
                proccessQueuePush(readyQueue, currentExec); // Move currently executing process to ready queue
                currentExec = &procs[nextProc]; // Update currently executing process
            } else { // Add new process to ready queue
                processQueuePush(readyQueue, &procs[nextProc++]);
            }

            nextProc++; // Move index to next arriving process
        }

        time += TIME_STEP; // Increment time
    }
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}
