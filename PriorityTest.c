#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;           // Process ID
    int bt;            // Burst time
    int remaining_bt;  // Remaining burst time (for preemption)
    int at;            // Arrival time
    int priority;      // Priority
    int tat;           // Turnaround time
    int wt;            // Waiting time
    int ct;            // Completion time
};

// Comparator function to sort processes based on arrival time, then priority
int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;

    // Sort by arrival time, and by priority if arrival times are equal
    if (p1->at == p2->at) {
        return p1->priority - p2->priority;
    }
    return p1->at - p2->at;
}

void preemptivePriorityScheduling(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;
    int i;
    int completionCounter = 1;

    // Sort the processes based on arrival time and priority
    qsort(proc, n, sizeof(struct Process), compare);

    // To keep track of processes that are ready to execute
    int isCompleted[n];
    for (i = 0; i < n; i++) {
        isCompleted[i] = 0;
        proc[i].remaining_bt = proc[i].bt;  // Set remaining burst time initially equal to burst time
    }

    while (completed < n) {
        int idx = -1;
        int minPriority = 1000;  // Start with a high priority value

        // Find the process with the highest priority that is ready to execute
        for (i = 0; i < n; i++) {
            if (proc[i].at <= currentTime && !isCompleted[i] && proc[i].priority < minPriority && proc[i].remaining_bt > 0) {
                minPriority = proc[i].priority;
                idx = i;
            }
        }

        // If no process is ready, increment current time
        if (idx == -1) {
            currentTime++;
            continue;
        }

        // Execute the process (reduce its remaining burst time by 1)
        proc[idx].remaining_bt--;
        currentTime++;

        // If the process finishes, mark it as completed
        if (proc[idx].remaining_bt == 0) {
            proc[idx].ct = currentTime;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
            isCompleted[idx] = 1;
            completed++;

            // Print the completion counter progress
            printf("Completion counter: %d | Process %d completed at time %d\n",
                completionCounter, proc[idx].pid, proc[idx].ct);
            completionCounter++;
        }
    }

    // Calculate average waiting time and average turnaround time
    int totalWT = 0, totalTAT = 0;
    for (i = 0; i < n; i++) {
        totalWT += proc[i].wt;
        totalTAT += proc[i].tat;
    }

    float avgWT = (float)totalWT / n;
    float avgTAT = (float)totalTAT / n;

    // Print the final results
    printf("\nPID\tBurst Time\tArrival Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].bt, proc[i].at, proc[i].priority,
               proc[i].ct, proc[i].tat, proc[i].wt);
    }

    // Print average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %.2f\n", avgWT);
    printf("Average Turnaround Time: %.2f\n", avgTAT);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d:\n", i + 1);
        proc[i].pid = i + 1;  // Process ID
        printf("Burst time: ");
        scanf("%d", &proc[i].bt);
        printf("Arrival time: ");
        scanf("%d", &proc[i].at);
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
    }

    // Call the preemptive priority scheduling function
    preemptivePriorityScheduling(proc, n);

    return 0;
}
