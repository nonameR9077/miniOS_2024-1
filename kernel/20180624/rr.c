# include <stdio.h>

#define TIME_QUANTUM 2

typedef struct {
    int pid; // Process ID
    int burst_time; // Burst time (time required for execution)
    int remaining_time; // Remaining time for execution
} Process;

void roundRobinScheduler(Process processes[], int n) {
    int remaining_processes = n;
    int current_time = 0;

    // Run until all processes are completed
    while (remaining_processes > 0) {
        // Traverse through all processes
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                // Execute the process for the time quantum or its remaining time, whichever is smaller
                int execute_time = (processes[i].remaining_time < TIME_QUANTUM) ? processes[i].remaining_time : TIME_QUANTUM;

                // Update the remaining time and current time
                processes[i].remaining_time -= execute_time;
                current_time += execute_time;

                // Print process execution
                printf("Time %d: Process %d is executed for %d units\n", current_time, processes[i].pid, execute_time);

                // If the process is completed
                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                }
            }
        }
    }
}