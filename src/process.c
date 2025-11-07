#include <stdio.h>
#include <stdlib.h>

#include "../include/process.h"


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

    return procA->arrivalTime - procB->arrivalTime;
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


