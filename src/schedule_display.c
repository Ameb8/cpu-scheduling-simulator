#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/fmt.h"
#include "../include/schedule_display.h"


#define PROC_TABLE_DIV "+------------+--------------+------------+----------------+--------------+-----------------+"
#define PROC_COLORS 6

#define BOOL char
#define TRUE 1
#define FALSE 0


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


void execProcessTable(Process*** procs, int* completionTimes, int numProcs) {
    BOOL* isFinished = calloc(numProcs, sizeof(BOOL));
    size_t numFinished = 0;
    int time = 0;
    
    printf("\n");
    printf("+--------------------------------+\n");

    while(numFinished < numProcs) {
        printf("|%d|", time + 1);

        for(int i = 0; i < numProcs; i++) {
            char *color = ASC_RESET;
            int process = INT_MIN;

            if(time < completionTimes[i]) { // 
                if(procs[i][time]) { // Assign color  and value to process
                    process = procs[i][time]->processId; // Get running process ID

                    switch (process % PROC_COLORS) { // Assign cell color
                        case 1: color = ASC_RED_BG; break;
                        case 2: color = ASC_GREEN_BG; break;
                        case 3: color = ASC_YELLOW_BG; break;
                        case 4: color = ASC_BLUE_BG; break;
                        case 5: color = ASC_MAGENTA_BG; break;
                        case 6: color = ASC_CYAN_BG; break;
                        default: color = ASC_RESET; break;
                    }
                }
            } else if(time == completionTimes[i]) { // Process finished
                numFinished++;
            }
            
            if(process != INT_MIN) // Display running process
                printf("%s%s %d %s|", ASC_BOLD, color, process, ASC_RESET);
            else // Display empty cell
                printf("%s%s   %s|", ASC_BOLD, color, ASC_RESET);

            
        }

        // Advance time unit
        printf("\n+--------------------------------+\n");
        time++;
    }

    printf("\n");
}