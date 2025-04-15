#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define TOTAL_TIME_UNITS 100

typedef struct {
    int id;
    int share;       // Share (weight) assigned to process
    int executed;    // Total units executed
    float ratio;     // Ideal execution ratio
    float deficit;   // Difference between ideal and actual
} Process;

void proportional_scheduling(Process processes[], int n) {
    int total_shares = 0;
    for (int i = 0; i < n; i++) {
        total_shares += processes[i].share;
    }

    for (int i = 0; i < n; i++) {
        processes[i].ratio = (float)processes[i].share / total_shares;
        processes[i].executed = 0;
        processes[i].deficit = 0;
    }

    printf("\n--- Proportional Share Scheduling ---\n");

    for (int t = 0; t < TOTAL_TIME_UNITS; t++) {
        int selected = -1;
        float max_deficit = -1.0;

        // Update deficits
        for (int i = 0; i < n; i++) {
            processes[i].deficit += processes[i].ratio;

            // Find the process with the highest deficit
            if (processes[i].deficit > max_deficit) {
                max_deficit = processes[i].deficit;
                selected = i;
            }
        }

        // Execute the selected process
        processes[selected].executed++;
        processes[selected].deficit -= 1.0;

        printf("Time %3d: Process P%d executed (Share: %d)\n", t, processes[selected].id, processes[selected].share);
    }

    printf("\n--- Execution Summary ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d executed for %d units (Expected: ~%.1f)\n",
               processes[i].id,
               processes[i].executed,
               processes[i].ratio * TOTAL_TIME_UNITS);
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n > MAX_PROCESSES || n <= 0) {
        printf("Invalid number of processes. Max is %d.\n", MAX_PROCESSES);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter share (weight) for Process P%d: ", i + 1);
        scanf("%d", &processes[i].share);
    }

    proportional_scheduling(processes, n);

    return 0;
}
