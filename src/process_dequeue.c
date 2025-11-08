#include <stdio.h>
#include <stdlib.h>

#include "../include/process_dequeue.h"

#define BOOL char
#define TRUE 1
#define FALSE 0

typedef struct QueueNode {
    struct QueueNode* next;
    Process* process;
} QueueNode;


struct ProcessDequeue {
    QueueNode* head;
    QueueNode* tail;
    size_t size;
};


QueueNode* QueueNodeInit(Process* p) {
    QueueNode* node = malloc(sizeof(QueueNode)); // Allocate memory
    node->next = NULL; // Initialize next pointer ot null
    node->process = p; // Initialize process field
}


ProcessDequeue* processDequeueInit() {
    // Allocates zeroed-out heap memory for ProcessDequeue
    return calloc(1, sizeof(ProcessDequeue));
}


void processDequeueFree(ProcessDequeue* procQueue) {
    if(!procQueue) // Validate input
        return;

    while(procQueue->head) { // Free Nodes in queue
        procQueue->tail = procQueue->head;
        free(procQueue->head);
        procQueue->head = procQueue->tail;
    }

    free(procQueue); // Free Queue
}



BOOL processDequeueAppend(ProcessDequeue* procQueue, Process* process) {
    if(!procQueue || !process) // Validate inputs
        return FALSE;

    QueueNode* newNode = QueueNodeInit(process); // Create new node

    if(!newNode) // Memory allocation error
        return FALSE;

    procQueue->size += 1; // Increment dequeue size
 
    if(!procQueue->head) { // Queue empty
        procQueue->head = newNode;
        procQueue->tail = newNode;
    } else { // // Append to back
        procQueue->tail->next = newNode;
        procQueue->tail = newNode;
    }
 
    return TRUE;
}  


Process* processDequeuePoll(ProcessDequeue* procQueue) {
    if(!procQueue || !procQueue->head) // Empty or null ring
        return NULL;

    Process* headProc = procQueue->head->process; // Process to return
    procQueue->size -= 1; // Decrement dequeue size

    if(procQueue->size == 1) { // Remove only element
        procQueue->head = NULL;
        procQueue->tail = NULL;
    } else { // Remove leading process
        QueueNode* newHead = procQueue->head->next;
        free(procQueue->head);
        procQueue->head = newHead;
    }

    return headProc;
}


// Return current process without advancing
Process* processDequeuePeek(ProcessDequeue* procQueue) {
    if(!procQueue || !procQueue->head) // Empty or null ring
        return NULL;

    return procQueue->head->process;
}


size_t processDequeueSize(ProcessDequeue* procQueue) {
    if(procQueue) // Return size if non-null ring
        return procQueue->size;
    
    return 0;
}


void processDequeueMap(ProcessDequeue* procQueue, void (f)(Process*)) {
    if(!procQueue || !f) // Validate inputs
        return;

    QueueNode* iterator = procQueue->head; // Temp node for iteration

    while(iterator) { // Apply function to each process
        f(iterator->process);
        iterator = iterator->next;
    }

}
