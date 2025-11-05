#include <stdio.h>
#include <stdlib.h>

#include "../include/process_queue.h"


// Index of parents/children in heap from on current index
#define PARENT(i) (i / 2)
#define LEFT_CHILD(i) (2 * i)
#define RIGHT_CHILD(i) (2 * i + 1)


typedef struct {
    Process** processes; // Heap to store processes
    size_t capacity; // Maximum heap capacity
    size_t size; // Number of elements in heap
} ProcessQueue;


ProcessQueue* processQueueInit(size_t capacity) {
    if(capacity < 1) // Ensure valid capacity
        return NULL;

    // Allocate memory for ProcessQueue
    ProcessQueue* procQueue = malloc(sizeof(ProcessQueue));

    if(!procQueue) // Error allocating memory
        return NULL;

    // Allocate memory for heap
    procQueue->processes = malloc(capacity * sizeof(Process));

    // Error creating process queue
    if(!procQueue->processes) {
        free(procQueue);
        return NULL;
    }

    // Initialize fields
    procQueue->capacity = capacity;
    procQueue->size = 0;

    return procQueue;
}


void processQueueFree(ProcessQueue* procQueue) {
    if(procQueue) { // Free queue if non-null
        if(procQueue->processes) // Free heap if non-null
            free(procQueue->processes);

        free(procQueue);
    }
}


Process* processQueuePop(ProcessQueue* procQueue) {

}


Process* processQueuePeek(ProcessQueue* procQueue) {

}


char processQueuePush(ProcessQueue* procQueue, Process* process) {

}


size_t processQueueSize(ProcessQueue* procQueue) {

}