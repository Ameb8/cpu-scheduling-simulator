#include <stdio.h>
#include <stdlib.h>

#include "../include/process.h"


#define PROC_SCHED_LBL "\nProcess Scheduling Simulation Results:\n\n"


static int processCount = 0;

/*
typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int lastAck;
} Process; */


Process processInit(int arrivalTime, int burstTime) {
    return (Process) {
        processCount++, 
        arrivalTime, 
        burstTime, 
        burstTime,
        0,
        0, 
        0
    };
}


int cmpProcessArrival(const void* a, const void* b) {
    const Process* procA = (Process*)a;
    const Process* procB = (Process*)b;

    return procA->arrivalTime - procB->arrivalTime; // ascending order
}


int processExec(Process* p, int time, int curTime) {
    int execTime = time;

    if(time >= p->remainingTime)
        execTime = p->remainingTime;

    p->turnaroundTime += execTime;    
    p->remainingTime -= execTime;
    p->lastAck = curTime + execTime;
    
    return execTime;
}

void processWait(Process* p) {
    p->waitingTime++;
    p->turnaroundTime++;
}

void processResumeExec(Process* p, int curTime) {
    p->waitingTime += curTime - p->lastAck;
    p->turnaroundTime += curTime - p->lastAck;
}


void processSortArrival(Process processes[], int n) {
    qsort(processes, n, sizeof(Process), cmpProcessArrival);
}

void processPrint(const Process *p) {
    if (p == NULL) return;

    printf("+------------+--------------+------------+----------------+--------------+-----------------+\n");
    printf("| Process ID | Arrival Time | Burst Time | Remaining Time | Waiting Time | Turnaround Time |\n");
    printf("+------------+--------------+------------+----------------+--------------+-----------------+\n");
    printf("| %10d | %12d | %10d | %14d | %12d | %15d |\n",
           p->processId,
           p->arrivalTime,
           p->burstTime,
           p->remainingTime,
           p->waitingTime,
           p->turnaroundTime);
    printf("+------------+--------------+------------+----------------+--------------+-----------------+\n");
}