#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/schedule_display.h"


#define PROC_TABLE_DIV "+------------+--------------+------------+----------------+--------------+-----------------+"
#define PROC_COLORS 6


#define BOOL char
#define TRUE 1
#define FALSE 0

#define SIM_TABLE_HEADERS {"RR 2", "RR 4", "RR 6", "RR 8", "SJF "}

#define METRICS_TABLE_SEP "\n+--------+---------+------------+\n"


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
    if(!p) // Validate inputs 
        return;

    processPrintHeader(linePrefix);
    processPrintBody(p, linePrefix);
}

void processPrintTable(const Process* procs, size_t numProcs, const char* linePrefix) {
    if(!procs || numProcs < 1) // Validate inputs
        return;

    processPrintHeader(linePrefix); // Print table header
    
    for(int i = 0; i < numProcs; i++) // Print Process Items
        processPrintBody(&procs[i], linePrefix); 

}
/*
void execProcessPrint(const Process* p) {
    printf(EXEC_HEADER);
    processPrint(p, (LINE_START "\t"));
    printf(LINE_START "\n" LINE_START "\n" LINE_START);
}*/


static inline char* cellColor(int processId) {
    switch (processId % PROC_COLORS) {
        case 0: return ASC_CYAN_BG; break;
        case 1: return ASC_BLUE_BG; break;
        case 2: return ASC_GREEN_BG; break;
        case 3: return ASC_MAGENTA_BG; break;
        case 4: return ASC_RED_BG; break;
        case 5: return ASC_YELLOW_BG; break;
        default: return ASC_RESET; break;
    }
}


BOOL calculateMetrics(Process* procs, int numProcs, double* avgWait, double* avgTurnaround) {
    // Validate inputs
    if(!procs || !avgWait || !avgTurnaround || numProcs < 1)
        return FALSE;
    
    // Initialize metrics to zero
    *avgWait = 0;
    *avgTurnaround = 0;

    // Sum wait and turnaround times for all processes
    for(int i = 0; i < numProcs; i++) {
        *avgWait += procs[i].waitingTime;
        *avgTurnaround += procs[i].turnaroundTime;
    }

    // Average out results
    *avgWait /= numProcs;
    *avgTurnaround /= numProcs;

    return TRUE;
}


void metricsProcessTable(Process procs[][NUM_PROCS], int numSims, int numProcs) {
    double wait, turnaround; // Vars to store metrics
    const char* simHeaders[] = SIM_TABLE_HEADERS;

    printf(METRICS_TABLE_SEP);
    printf("|        | " ASC_GREEN_FG ASC_BOLD " Wait  " ASC_RESET " |" ASC_GREEN_FG ASC_BOLD " Turnaround " ASC_RESET "|");

    // Print header columns;
    printf(METRICS_TABLE_SEP);

    // Print RR Metrics
    for(int i = 0; i < numSims; i++) {
        // print rr header
        printf("|" ASC_BOLD ASC_CYAN_FG "  %s  " ASC_RESET "|", simHeaders[i]);

        calculateMetrics(procs[i], numProcs, &wait, &turnaround); // Calculate sim metrics

        printf(ASC_BOLD " %07.4f " ASC_RESET "|", wait);
        printf(ASC_BOLD "  %07.4f   " ASC_RESET "|", turnaround);

        printf(METRICS_TABLE_SEP);

    }
}


void execProcessTable(Process*** procs, int* completionTimes, int numProcs) {
    size_t numFinished = 0;
    int time = 0;

    const int COL_WIDTH = 8; // Width of each column
    const int TIME_COL_WIDTH = 6; // Width of time column

    // Print header
    printf("\n");

    // Print top border
    printf("+");
    printf("%-*s+", TIME_COL_WIDTH, "------"); // time column border
    
    for(int i = 0; i < numProcs; i++) // process columns border
        printf("%-*s+", COL_WIDTH, "--------"); 
    
    printf("\n|" ASC_BOLD ASC_GREEN_FG "%-*s" ASC_RESET "|", TIME_COL_WIDTH - 1, " Time "); // Time header

    for(int i = 0; i < numProcs - 1; i++) // Print RR Headers
        printf(ASC_BOLD ASC_GREEN_FG "  RR %d  " ASC_RESET "|", (i + 1) * 2); 

    // Print SJF Header
    printf(ASC_BOLD ASC_GREEN_FG "  SJF   " ASC_RESET "|");

    // Print header bottom border
    printf("\n+");
    printf("%-*s+", TIME_COL_WIDTH, "------");
    
    for(int i = 0; i < numProcs; i++) // Print sim col headers
        printf("%-*s+", COL_WIDTH, "--------");
    
    printf("\n");

    // Start printing table rows
    while(numFinished < numProcs) { // Iterate through time units
        printf("|" ASC_BOLD ASC_BLUE_FG " %-*d" ASC_RESET "|", TIME_COL_WIDTH - 1, time + 1); // Time column

        for(int i = 0; i < numProcs; i++) { // Iterate through time units
            // Set default for color and process id
            char *color = ASC_RESET;
            int process = INT_MIN;

            if(time < completionTimes[i]) { // Iterate each sim at time unit
                if(procs[i][time]) { // Process executing
                    process = procs[i][time]->processId;
                    color = cellColor(process); // Assign color
                }
            } else if(time == completionTimes[i]) { // Sim completed
                numFinished++;
            }

            if(process != INT_MIN) // Print process
                printf("%s%s  %d %*s%s|", ASC_BOLD, color, process, COL_WIDTH - 4, "", ASC_RESET);
            else // Empty cell
                printf("%-*s|", COL_WIDTH, " "); // Empty cell
        }

        // End row
        printf("\n");

        // Print row border
        printf("+");
        printf("%-*s+", TIME_COL_WIDTH, "------"); // Time col border

        for(int i = 0; i < numProcs; i++) {// Sim col borders
            if(procs[i][time] && procs[i][time + 1] && procs[i][time]->processId == procs[i][time + 1]->processId)
                printf("%s%-*s" ASC_RESET "+", cellColor(procs[i][time]->processId), COL_WIDTH, " ");
            else 
                printf("%-*s+", COL_WIDTH, "--------");
        }

        printf("\n");
        time++; // Increment time
    }

    printf("\n");

}
