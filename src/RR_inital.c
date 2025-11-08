
#include <stdio.h>
#include <stdlib.h>

#include "../include/process.h"
#include "../include/process_dequeue.h"

/*

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Your code
    
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
   // Your code
}
*/


void roundRobin(Process proc[], int numProcs, int quantum) {
    int time = 0; // Tracks time from epoch
    int timeQ = 0; // Tracks time from process switch synced with quantum
    int procIdx = 0; // Index of next arriving process

    ProcessDequeue* readyQueue = processDequeueInit(); // Queue of ready processes
    Process* currentExec = NULL; // Currently executing process

    // Loop by 1 time unit until all process complete execution
    while(procIdx < numProcs || processDequeueSize(readyQueue) == 0) {
        // Append arriving processes to queue
        while(procIdx < numProcs && proc[procIdx].arrivalTime == time)
            processDequeueAppend(readyQueue, &proc[procIdx++]);

        if(currentExec) { // Update current executing process if necessary
            if(timeQ % quantum == quantum - 1) // End of quantum reached
                processDequeueAppend(readyQueue, currentExec); // Add process to end of dequeue
            else if(currentExec->process->remainingTime == 0) // Process finished executing
                timeQ = 0; // Update time quantum count           

            currentExec = processDequeuePoll(readyQueue); // Update executing process
        }

        // Update process metrics
        if(currentExec) processExec(currentExec, 1, time);
        processDequeueMap(readyQueue, processWait);
    
        time++; // Move time forward
    }

}


/*
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}


int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
*/