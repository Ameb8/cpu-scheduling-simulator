#include <stdio.h>
#include <stdlib.h>

#include "../include/process_ring.h"

typedef struct RingNode {
    struct RingNode* next;
    Process* process;
} RingNode;


struct ProcessRing {
    RingNode* current;
    RingNode* last;
    size_t size;
};


RingNode* ringNodeInit(Process* p) {
    RingNode* node = malloc(sizeof(RingNode)); // Allocate memory
    node->process = p; // Initialize process field
}


ProcessRing* processRingInit() {
    // Allocates zeroed-out heap memory for ProcessRing
    return calloc(1, sizeof(ProcessRing));
}


void processRingFree(ProcessRing* procRing) {
    if(!procRing)
        return;

    while(procRing->current) {
        RingNode* cur = procRing->current;
        procRing->current = procRing->current->next;
        free(cur);
    }

    free(procRing);
}


Process* processRingPoll(ProcessRing* procRing) {
    if(!procRing || !procRing->current) // Empty or null ring
        return NULL;

    Process* p = procRing->current->process;

    if(!procRing->last) { // Remove only element
        procRing->current = NULL;   
    } else { // Remove current element
        procRing->current = procRing->current->next;
    }

    return p;
}


char processRingInsert(ProcessRing* procRing, Process* process) {
    if(!procRing || !process) // Validate inputs
        return 0;

    RingNode* newNode = ringNodeInit(process);

    if(!procRing->current) { // Ring is empty
        procRing->current = newNode;
    } else { // Add to end
        newNode->next = procRing->current;

        if(procRing->last) {
            procRing->last->next = newNode;
        } else {
            procRing->last = newNode;
            procRing->current->next = newNode;
        }
    }

    return 1;
}  


Process* processRingNext(ProcessRing* procRing) {
    if(!procRing || !procRing->current) // Empty or null ring
        return NULL;

    Process* p = procRing->current->process; // Holds next process
    procRing->size += 1; // Increment size

    if(procRing->last) { // Update pointers when size > 1
        procRing->last = procRing->current;
        procRing->current = procRing->current->next;
    }

    return p;
}


// Return current process without advancing
Process* processRingPeek(ProcessRing* procRing) {
    if(!procRing || !procRing->current) // Empty or null ring
        return NULL;

    return procRing->current->process;
}


size_t processRingSize(ProcessRing* procRing) {
    if(procRing) // Return size if non-null ring
        return procRing->size;
    
    return 0;
}
