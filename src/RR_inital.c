/*
#include <stdio.h>
#include <stdlib.h>

#include "../include/process.h"


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
    int time = 0;
    int numWaitingWaiting = 0;

    for(int i = 0; i < numProcs; i++) {
    
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