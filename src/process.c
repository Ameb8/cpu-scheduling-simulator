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
        arrivalTime, 
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

void processResumeExec(Process* p, int curTime) {
    p->waitingTime += curTime - p->lastAck;
    p->turnaroundTime += curTime - p->lastAck;
}


void processSortArrival(Process processes[], int n) {
    qsort(processes, n, sizeof(Process), cmpProcessArrival);
}

/*
void processOutputScheduling(Process processes[], int n) {
    printf(PROC_SCHED_LBL);

    for(int i = 0; i < n; i++) {

    }
}*/