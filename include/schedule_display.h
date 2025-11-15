#ifndef SCHEDULE_DISPLAY_H
#define SCHEDULE_DISPLAY_H


#include "process.h"


#define NUM_PROCS 4 // Number of arriving processes

// ANSI escape codes
#define ASC_RESET "\x1b[0m" // Resets formatting
#define ASC_BOLD "\x1b[1m" // Makes text bold

// ANSI escape codes to set terminal output text color
#define ASC_RED_FG "\x1b[31m"
#define ASC_GREEN_FG "\x1b[32m"
#define ASC_YELLOW_FG   "\x1b[33m"
#define ASC_BLUE_FG "\x1b[34m"
#define ASC_MAGENTA_FG  "\x1b[35m"
#define ASC_CYAN_FG     "\x1b[36m"

// ANSI escape codes to set terminal output background color
#define ASC_RED_BG      "\x1b[41m"
#define ASC_GREEN_BG    "\x1b[42m"
#define ASC_YELLOW_BG   "\x1b[43m"
#define ASC_BLUE_BG     "\x1b[44m"
#define ASC_MAGENTA_BG  "\x1b[45m"
#define ASC_CYAN_BG     "\x1b[46m"


void processPrintTable(const Process* procs, size_t numProcs, const char* linePrefix);
void metricsProcessTable(Process procs[][NUM_PROCS], int numSims, int numProcs);
void execProcessTable(Process*** procs, int* completionTimes, int numProcs);
char calculateMetrics(Process* procs, int numProcs, double* avgWait, double* avgTurnaround);


#endif