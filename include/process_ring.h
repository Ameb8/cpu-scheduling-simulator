#ifndef PROCESS_RING_H
#define PROCESS_RING_H

#include <stdio.h>

#include "process.h"

typedef struct ProcessRing ProcessRing;

ProcessRing* processRingInit();
void processRingFree(ProcessRing* procRing);
Process* processRingPeek(ProcessRing* procRing);
Process* processRingPoll(ProcessRing* procRing);
char processRingInsert(ProcessRing* procRing, Process* p);
Process* processRingNext(ProcessRing* procRing);
size_t processRingSize(ProcessRing* procRing);
void processRingMap(ProcessRing* procRing, void (f)(Process*));


#endif
