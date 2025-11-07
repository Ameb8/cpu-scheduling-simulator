#include <stdio.h>

#include "../include/fmt.h"
#include "../include/schedule_display.h"


#define PROC_TABLE_DIV "+------------+--------------+------------+----------------+--------------+-----------------+"


void processPrintHeader(const char* linePrefix) {
    printf("%s" PROC_TABLE_DIV "\n", linePrefix);
    printf("%s| Process ID | Arrival Time | Burst Time | Remaining Time | Waiting Time | Turnaround Time |\n", linePrefix);
    printf("%s" PROC_TABLE_DIV "\n", linePrefix);
}


void processPrintBody(const Process* p, const char* linePrefix) {
    printf(
        "%s| %10d | %12d | %10d | %14d | %12d | %15d |\n",
        linePrefix,
        p->processId,
        p->arrivalTime,
        p->burstTime,
        p->remainingTime,
        p->waitingTime,
        p->turnaroundTime
    );

    printf("%s" PROC_TABLE_DIV "\n", linePrefix);
}


void processPrint(const Process* p, const char* linePrefix) {
    if (p == NULL) return;

    processPrintHeader(linePrefix);
    processPrintBody(p, linePrefix);
}

void execProcessPrint(const Process* p) {
    printf(EXEC_HEADER);
    processPrint(p, (LINE_START "\t"));
    printf(LINE_START "\n" LINE_START "\n" LINE_START);
}

