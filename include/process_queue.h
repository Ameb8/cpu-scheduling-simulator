#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include <stdio.h>
#include "process.h"

typedef struct ProcessQueue;

ProcessQueue* processQueueInit(size_t capacity); // Initializes empty queue of defined max capacity
void processQueueFree(ProcessQueue* procQueue); // Deallocate process queue memory
Process* processQueuePop(ProcessQueue* procQueue); // Add new process to queue
Process* processQueuePeek(ProcessQueue* procQueue); // View next element in queue without removing
char processQueuePush(ProcessQueue* procQueue, Process* process); // Get next item from process queue
size_t processQueueSize(ProcessQueue* procQueue); // Retrieve number of elements in queue

#endif
