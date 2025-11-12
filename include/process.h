#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
} Process;

Process processInit(int arrivalTime, int burstTime);
void processSortArrival(Process processes[], int n);
int processExec(Process* p, int time, int curTime);
void processWait(Process* p);
void processResumeExec(Process* p, int curTime);
void growProcessArr(Process***, int size, int newSize);


#endif