#ifndef SJF_SIM_H
#define SJF_SIM_H

#include "process.h"

Process** sjfSimulate(Process procs[], int numProcs, int* totalTime);

#endif