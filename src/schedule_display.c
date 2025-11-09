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

/*
void execProcessTable(Process*** procs, int* completionTimes, int numProcs) {
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
                        case 0: color = ASC_CYAN_BG; break;
                        case 1: color = ASC_BLUE_BG; break;
                        case 2: color = ASC_GREEN_BG; break;
                        case 3: color = ASC_MAGENTA_BG; break;
                        case 4: color = ASC_RED_BG; break;
                        case 5: color = ASC_YELLOW_BG; break;
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
}*/



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

    for(int i = 0; i < numProcs; i++) // Print RR Headers
        printf(ASC_BOLD ASC_GREEN_FG "  RR %d  " ASC_RESET "|", (i + 1) * 2); 

    // Print SJF Header


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

                    // Assign color
                    switch (process % PROC_COLORS) {
                        case 0: color = ASC_CYAN_BG; break;
                        case 1: color = ASC_BLUE_BG; break;
                        case 2: color = ASC_GREEN_BG; break;
                        case 3: color = ASC_MAGENTA_BG; break;
                        case 4: color = ASC_RED_BG; break;
                        case 5: color = ASC_YELLOW_BG; break;
                        default: color = ASC_RESET; break;
                    }
                }
            } else if(time == completionTimes[i]) { // Sim ccompleted
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

        for(int i = 0; i < numProcs; i++) // Sim col borders
            printf("%-*s+", COL_WIDTH, "--------");
        
        printf("\n");
        time++; // Increment time
    }

    printf("\n");
}
