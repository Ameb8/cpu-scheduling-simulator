#ifndef SCHEDULE_DISPLAY_H
#define SCHEDULE_DISPLAY_H


#include "process.h"

#define NUM_PROCS 4

#define ASC_RESET "\x1b[0m"
#define ASC_BOLD "\x1b[1m"

#define ASC_RED_FG "\x1b[31m"
#define ASC_GREEN_FG "\x1b[32m"
#define ASC_YELLOW_FG   "\x1b[33m"
#define ASC_BLUE_FG "\x1b[34m"
#define ASC_MAGENTA_FG  "\x1b[35m"
#define ASC_CYAN_FG     "\x1b[36m"


#define ASC_RED_BG      "\x1b[41m"
#define ASC_GREEN_BG    "\x1b[42m"
#define ASC_YELLOW_BG   "\x1b[43m"
#define ASC_BLUE_BG     "\x1b[44m"
#define ASC_MAGENTA_BG  "\x1b[45m"
#define ASC_CYAN_BG     "\x1b[46m"

#define LINE_START ASC_BLUE_FG "|" ASC_RESET

#define TIME_SEPARATOR ASC_BLUE_FG "+-------------------------------------------------------------------------------------------------------------------------------+" ASC_RESET
#define SEPARATOR "+-------------------------------------------------------------------------+"
#define SHORT_SEPARATOR "+------------------------------------------------------------------------------------------+"

#define TIME_HEADER LINE_START "\n" TIME_SEPARATOR "\n" LINE_START "\t\t" ASC_BOLD ASC_GREEN_FG "Time:\t%d\t\t\t\t\t\t\t\t\t\t\t\t\t" ASC_RESET LINE_START "\n" TIME_SEPARATOR ASC_RESET "\n" LINE_START
#define EXEC_HEADER "\n" LINE_START "\n" LINE_START "\t" SHORT_SEPARATOR "\n" LINE_START "\t" "|\t" ASC_BOLD ASC_YELLOW_FG "Currently Executing Process \t\t\t\t\t\t\t   " ASC_RESET "|\n"
#define ARRIVE_HEADER LINE_START "\n" LINE_START "\t" SHORT_SEPARATOR "\n" LINE_START "\t|\t" ASC_BOLD ASC_CYAN_FG "Arriving Processes\t\t\t\t\t\t\t\t   " ASC_RESET "|\n"
#define READY_QUEUE_HEADER "\n" LINE_START "\t" SHORT_SEPARATOR "\n" LINE_START "\t|\t" ASC_BOLD ASC_MAGENTA_FG "Processes in Ready Queue\t\t\t\t\t\t\t   " ASC_RESET "|\n"


void processPrintHeader(const char* linePrefix);
void processPrintBody(const Process* p, const char* linePrefix);
void processPrint(const Process *p, const char* linePrefix);
void execProcessPrint(const Process* p);
void metricsProcessTable(Process procs[][NUM_PROCS], int numSims, int numProcs);
void execProcessTable(Process*** procs, int* completionTimes, int numProcs);
char calculateMetrics(Process* procs, int numProcs, double* avgWait, double* avgTurnaround);
 
#endif