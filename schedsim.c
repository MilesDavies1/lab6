#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "util.h"

// Signature for the comparer function
typedef int (*Comparer)(const void *a, const void *b);

// Struct to hold start and end indexes for sorting
typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

// Function to find the waiting time for all processes using FCFS
void findWaitingTimeFCFS(ProcessType plist[], int n)
{
    // Function to find turn around time for all processes
    findTurnAroundTime(plist, n);
}

// Function to find the waiting time for all processes using Priority
void findWaitingTimePriority(ProcessType plist[], int n)
{
    // Sort the processes based on priority
    qsort(plist, n, sizeof(ProcessType), my_comparer);

    // Calculate waiting times
    plist[0].wt = 0; // First process has 0 waiting time

    // Calculate waiting times for the rest of the processes
    for (int i = 1; i < n; i++) {
        plist[i].wt = plist[i - 1].bt + plist[i - 1].wt;
    }
}

// Function to find the waiting time for all processes using SJF
void findWaitingTimeSJF(ProcessType plist[], int n)
{
    // Sort the processes based on burst time (SJF)
    qsort(plist, n, sizeof(ProcessType), my_comparer);

    // Calculate waiting times
    plist[0].wt = 0; // First process has 0 waiting time

    // Calculate waiting times for the rest of the processes
    for (int i = 1; i < n; i++) {
        plist[i].wt = plist[i - 1].bt + plist[i - 1].wt;
    }
}

// Function to find the waiting time for all processes using RR
void findWaitingTimeRR(ProcessType plist[], int n, int quantum)
{
    int remaining_burst[n];
    for (int i = 0; i < n; i++) {
        remaining_burst[i] = plist[i].bt;
    }

    int t = 0; // Current time

    while (1) {
        int done = 1;

        // Traverse all processes
        for (int i = 0; i < n; i++) {
            // If burst time is greater than 0, then the process is not done
            if (remaining_burst[i] > 0) {
                done = 0; // Set done to false

                if (remaining_burst[i] > quantum) {
                    t += quantum;
                    remaining_burst[i] -= quantum;
                } else {
                    t += remaining_burst[i];
                    plist[i].wt = t - plist[i].bt;
                    remaining_burst[i] = 0; // Process is done
                }
            }
        }

        // If all processes are done, exit the loop
        if (done == 1) {
            break;
        }
    }
}

// Function to calculate average time
void findavgTimeRR(ProcessType plist[], int n, int quantum)
{
    // Function to find waiting time of all processes using RR
    findWaitingTimeRR(plist, n, quantum);

    // Display processes along with all details
    printf("\n*********\nRR Quantum = %d\n", quantum);

    // Print metrics
    printMetrics(plist, n);
}

// Function to calculate average time
void findavgTimeFCFS(ProcessType plist[], int n)
{
    // Function to find waiting time of all processes using FCFS
    findWaitingTimeFCFS(plist, n);
 
    // Display processes along with all details
    printf("\n*********\nFCFS\n");

    // Print metrics
    printMetrics(plist, n);
}

// Function to find the waiting time for all processes using SJF
void findWaitingTimeSJF(ProcessType plist[], int n)
{
    // Sort the processes based on burst time (SJF)
    qsort(plist, n, sizeof(ProcessType), my_comparer);

    // Calculate waiting times
    plist[0].wt = 0; // First process has 0 waiting time

    // Calculate waiting times for the rest of the processes
    for (int i = 1; i < n; i++) {
        plist[i].wt = plist[i - 1].bt + plist[i - 1].wt;
    }
}

// Function to calculate average time
void findavgTimeSJF(ProcessType plist[], int n)
{
    // Function to find waiting time of all processes using SJF
    findWaitingTimeSJF(plist, n);
 
    // Display processes along with all details
    printf("\n*********\nSJF\n");

    // Print metrics
    printMetrics(plist, n);
}

// Function to find the waiting time for all processes using Priority
void findWaitingTimePriority(ProcessType plist[], int n)
{
    // Sort the processes based on priority
    qsort(plist, n, sizeof(ProcessType), my_comparer);

    // Calculate waiting times
    plist[0].wt = 0; // First process has 0 waiting time

    // Calculate waiting times for the rest of the processes
    for (int i = 1; i < n; i++) {
        plist[i].wt = plist[i - 1].bt + plist[i - 1].wt;
    }
}

// Function to calculate average time
void findavgTimePriority(ProcessType plist[], int n)
{
    // Function to find waiting time of all processes using Priority
    findWaitingTimePriority(plist, n);
 
    // Display processes along with all details
    printf("\n*********\nPriority\n");

    // Print metrics
    printMetrics(plist, n);
}

// Function to calculate turn around time
void findTurnAroundTime(ProcessType plist[], int n)
{
    // calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        plist[i].tat = plist[i].bt + plist[i].wt;
}

// Compare function for sorting processes based on priority
int my_comparer(const void *a, const void *b)
{
    ProcessType *process_a = (ProcessType *)a;
    ProcessType *process_b = (ProcessType *)b;

    if (process_a->pri < process_b->pri) {
        return 1;
    } else if (process_a->pri > process_b->pri) {
        return -1;
    } else {
        // If priority values are equal, compare based on arrival time
        return process_a->art - process_b->art;
    }
}

// Function to print process metrics
void printMetrics(ProcessType plist[], int n)
{
    int total_wt = 0, total_tat = 0;

    printf("\tProcesses\tBurst time\tWaiting time\tTurn around time\n");

    // Calculate total waiting time and total turn around time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + plist[i].wt;
        total_tat = total_tat + plist[i].tat;
        printf("\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].wt, plist[i].tat);
    }

    float awt = ((float)total_wt / (float)n);
    float att = ((float)total_tat / (float)n);

    printf("\nAverage waiting time = %.2f", awt);
    printf("\nAverage turn around time = %.2f\n", att);
}

// Function to initialize processes from a file
ProcessType *initProc(char *filename, int *n)
{
    FILE *input_file = fopen(filename, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Invalid filepath\n");
        fflush(stdout);
        exit(0);
    }

    ProcessType *plist = parse_file(input_file, n);

    fclose(input_file);

    return plist;
}

// Driver code
int main(int argc, char *argv[])
{
    int n;
    int quantum = 2;

    ProcessType *proc_list;

    if (argc < 2) {
        fprintf(stderr, "Usage: ./schedsim <input-file-path>\n");
        fflush(stdout);
        return 1;
    }

    // FCFS
    n = 0;
    proc_list = initProc(argv[1], &n);

    findavgTimeFCFS(proc_list, n);

    // SJF
    n = 0;
    proc_list = initProc(argv[1], &n);

    findavgTimeSJF(proc_list, n);

    // Priority
    n = 0;
    proc_list = initProc(argv[1], &n);

    findavgTimePriority(proc_list, n);

    // RR
    n = 0;
    proc_list = initProc(argv[1], &n);

    findavgTimeRR(proc_list, n, quantum);

    return 0;
}
