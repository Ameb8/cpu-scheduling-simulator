#include <stdio.h>
#include <stdlib.h>

#include "../include/process.h"


int cmpProcessArrival(const void* a, const void* b) {
    const Process* procA = (Process*)a;
    const Process* procB = (Process*)b;

    return procA->arrivalTime - procB->arrivalTime; // ascending order
}


typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int lastAck;
} Process;


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


void processOutputScheduling(Process processes[], int n) {
    
}