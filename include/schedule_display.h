#ifndef SCHEDULE_DISPLAY_H
#define SCHEDULE_DISPLAY_H


#include "process.h"


#define ASC_RESET "\x1b[0m"
#define ASC_BOLD "\x1b[1m"

#define ASC_RED_FG "\x1b[31m"
#define ASC_BLUE_FG "\x1b[34m"
#define ASC_GREEN_FG "\x1b[32m"

#define LINE_START ASC_BLUE_FG "|" ASC_RESET

#define TIME_SEPARATOR ASC_BLUE_FG "+-------------------------------------------------------------------------------------------------------------------------------+" ASC_RESET
#define SEPARATOR "+-------------------------------------------------------------------------+"
#define SHORT_SEPARATOR "+------------------------------------------------------------------------------------------+"

#define TIME_HEADER LINE_START "\n" TIME_SEPARATOR "\n" LINE_START "\t" ASC_BOLD ASC_GREEN_FG "Time:\t%d\t\t\t\t\t\t\t\t\t\t\t\t\t\t" ASC_RESET LINE_START "\n" TIME_SEPARATOR ASC_RESET "\n" LINE_START
#define READY_QUEUE_HEADER "\n" LINE_START "\t" SHORT_SEPARATOR "\n" LINE_START "\t|\t" ASC_BOLD "Processes in Ready Queue:\t\t\t\t\t\t\t   " ASC_RESET "|\n"

//(LINE_START ASC_GREEN_FG ASC_BOLD "\tProcesses in Ready Queue:\t\t\t\t\t" ASC_RESET "|\n\n")



void processPrintHeader(const char* linePrefix);
void processPrintBody(const Process* p, const char* linePrefix);
void processPrint(const Process *p, const char* linePrefix);
void execProcessPrint(const Process* p);

 

#endif