#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include <stdio.h>
#include "process.h"

typedef struct ProcessQueue ProcessQueue;

ProcessQueue* processQueueInit(size_t capacity); // Initializes empty queue of defined max capacity
void processQueueFree(ProcessQueue* procQueue); // Deallocate process queue memory
Process* processQueuePop(ProcessQueue* procQueue); // Get next item from process queue
Process* processQueuePeek(ProcessQueue* procQueue); // View next element in queue without removing
char processQueuePush(ProcessQueue* procQueue, Process* process); // Add new process to queue
size_t processQueueSize(ProcessQueue* procQueue); // Retrieve number of elements in queue
void processQueueMap(ProcessQueue* procQueue, void (*f)(Process*)); // Apply function to each element queue in priority order

#endif
