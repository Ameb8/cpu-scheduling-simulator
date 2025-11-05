#include <stdio.h>
#include <stdlib.h>

#include "../include/process_queue.h"


// Index of parents/children in heap from on current index
#define PARENT(i) ((i - 1) / 2)
#define LEFT_CHILD(i) (2 * i + 1)
#define RIGHT_CHILD(i) (2 * i + 2)


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
    procQueue->processes = malloc(capacity * sizeof(Process*));

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
    // Ensure at least 1 process is present
    if(!procQueue || !procQueue->processes || procQueue->size < 1)
        return NULL;

    Process* root = procQueue->processes[0]; // Get root element

    // Move last element to root
    procQueue->processes[0] = procQueue->processes[--procQueue->size];

    if(procQueue->size > 0) // Update heap structure
        heapifyDown(procQueue);

    return root;
}


Process* processQueuePeek(ProcessQueue* procQueue) {
    // Ensure at least 1 process is present
    if(!procQueue || !procQueue->processes || procQueue->size < 1)
        return NULL;

    return procQueue->processes[0];
}


char processQueuePush(ProcessQueue* procQueue, Process* process) {
    // Validate inputs
    if(!procQueue || !procQueue->processes || !process) 
        return 0;

    // Do not add if capacity reached
    if(procQueue->size >= procQueue->capacity)
        return 0;

    // Add new process to end of heap
    procQueue->processes[procQueue->size++] = process;

    heapifyUp(procQueue); // Update heap structure

    return 1;
}


size_t processQueueSize(ProcessQueue* procQueue) {
    return procQueue->size;
}


void heapifyUp(ProcessQueue* procQueue) {
    size_t idx = procQueue->size - 1;

    while(
        idx > 0 && 
        procQueue->processes[idx]->burst_time < procQueue->processes[PARENT(idx)]->burst_time
    ) {
        Process* temp = procQueue->processes[idx];
        procQueue->processes[idx] = procQueue->processes[PARENT(idx)];
        procQueue->processes[PARENT(idx)] = temp;

        idx = PARENT(idx);
    }
}


void heapifyDown(ProcessQueue* procQueue) {
    size_t idx = 0;

    while (1) {
        size_t left = LEFT_CHILD(idx);
        size_t right = RIGHT_CHILD(idx);
        size_t smallest = idx;

        if (left < procQueue->size && // Check if left child has shortest burst
            procQueue->processes[left]->burst_time < procQueue->processes[smallest]->burst_time) {
            smallest = left;
        }

        if (right < procQueue->size && // Check if right child has shortest burst
            procQueue->processes[right]->burst_time < procQueue->processes[smallest]->burst_time) {
            smallest = right;
        }

        if (smallest != idx) { // Swap elements
            Process* temp = procQueue->processes[idx];
            procQueue->processes[idx] = procQueue->processes[smallest];
            procQueue->processes[smallest] = temp;

            idx = smallest; // Move down heap
        } else { // Heap property restored
            break;
        }
    }
}
