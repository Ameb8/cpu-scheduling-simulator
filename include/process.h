#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int lastAck;
} Process;

void processSortArrival(Process processes[], int n);
int processExec(Process* p, int time, int curTime);
void processResumeExec(Process* p, int curTime);
void processPrintScheduling(Process processes[], int n)


#endif