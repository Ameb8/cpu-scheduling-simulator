#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/process.h"
#include "../include/sjf_sim.h"
#include "../include/rr_sim.h"
#include "../include/schedule_display.h"


#define NUM_PROCS 4
#define QUANTUMS {2, 4, 6, 8}
#define NUM_QUANTUMS 4
#define NUM_SIMS (NUM_QUANTUMS + 1)

#define SIM_TABLE_LBL ASC_MAGENTA_FG ASC_BOLD "\nProcess Execution Order:\n\n" ASC_RESET
#define METRICS_TABLE_LBL ASC_MAGENTA_FG ASC_BOLD "\nAverage Waiting and Turnaround Times:\n\n" ASC_RESET
#define SIM_FULL_NAMES {"Round Robin 2", "Round Robin 4", "Round Robin 6", "Round Robin 8", "Shortest Job First"}


int main() {
    // Initialize processes
    int initProcVals[NUM_PROCS][2] = {{0, 8}, {1, 4}, {2, 9}, {3, 5}}; 
    Process processes[NUM_PROCS];

    const char* simNames[NUM_SIMS] = SIM_FULL_NAMES;
    
    for(int i = 0; i < NUM_PROCS; i++)
        processes[i] = processInit(initProcVals[i][0], initProcVals[i][1]);

    const int rrQuantums[] = QUANTUMS;

    Process metrics[NUM_SIMS][NUM_PROCS] = {0}; // Stores Process metrics of each sim

    // Create copy of Processes for each sim to allow for in-place modification
    for(int i = 0; i < NUM_SIMS; i++)
        memcpy(metrics[i], processes, sizeof(Process) * NUM_PROCS);

    // Set array to hold resulting processes for each simulation         
    Process*** results = malloc(NUM_SIMS * sizeof(Process**));
    int resultSizes[NUM_SIMS] = {0};

    for(int i = 0; i < NUM_QUANTUMS; i++) // Run RR sims
        results[i] = rrSimulate(metrics[i], NUM_PROCS, rrQuantums[i], &resultSizes[i]);

    // Run SJF simulation
    results[NUM_QUANTUMS] = sjfSimulate(metrics[NUM_QUANTUMS], NUM_PROCS, &resultSizes[NUM_QUANTUMS]);

    printf(SIM_TABLE_LBL); // Label results table
    execProcessTable(results, resultSizes, NUM_SIMS); // Display results

    printf(METRICS_TABLE_LBL); // Label metrics table
    metricsProcessTable(metrics, NUM_SIMS, NUM_PROCS); // Display metrics

    // Display Metric results for each simulation
    for(int i = 0; i < NUM_SIMS; i++) {
        printf(ASC_MAGENTA_FG ASC_BOLD"\n\nProcess Metrics for " ASC_CYAN_FG "%s" ASC_RESET "\n\n", simNames[i]);
        processPrintTable(metrics[i], NUM_PROCS, "\t");
    }
 
    // Free results memory
    for(int i = 0; i < NUM_SIMS; i++) {
        if(results[i]) // Free each row
            free(results[i]);

    }

    free(results); // Free outer array
    return 0;
}


