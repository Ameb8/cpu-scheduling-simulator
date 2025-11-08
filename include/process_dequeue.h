#ifndef PROCESS_DEQUEUE_H
#define PROCESS_DEQUEUE_H

#include <stdio.h>

#include "process.h"

typedef struct ProcessDequeue ProcessDequeue;

ProcessDequeue* processDequeueInit();
void processDequeueFree(ProcessDequeue* procQueue);
Process* processDequeuePeek(ProcessDequeue* procQueue);
Process* processDequeuePoll(ProcessDequeue* procQueue);
char processDequeueInsert(ProcessDequeue* procQueue, Process* p);
size_t processDequeueSize(ProcessDequeue* procQueue);
void processDequeueMap(ProcessDequeue* procQueue, void (f)(Process*));
 

#endif
