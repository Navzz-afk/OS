#include <stdio.h>

typedef struct {
    int id;
    int burstTime;
    int remainingTime;
    int arrivalTime;
    int waitTime;
    int turnAroundTime;
    int completionTime;
} Process;

void sortProcessesByArrivalAndBurstTime(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime ||
                (processes[i].arrivalTime == processes[j].arrivalTime && processes[i].burstTime > processes[j].burstTime)) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void printResults(Process processes[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitTime, processes[i].turnAroundTime, processes[i].completionTime);
    }
}

void preemptiveSJF(Process processes[], int n) {
    int completed = 0, time = 0, minIndex;
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("\nProcess:\n");

    while (completed < n) {
        minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (minIndex == -1 || processes[i].remainingTime < processes[minIndex].remainingTime) {
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1) {
            processes[minIndex].remainingTime--;
            currentTime++;

            if (processes[minIndex].remainingTime == 0) {
                completed++;
                processes[minIndex].turnAroundTime = currentTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
                processes[minIndex].completionTime = currentTime;
            }
        } else {
            currentTime++;
        }
    }

    printResults(processes, n);
    calculateAverageTimes(processes, n);
}

void calculateAverageTimes(Process processes[], int n) {
    int totalWaitTime = 0, totalTurnAroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitTime += processes[i].waitTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    sortProcessesByArrivalAndBurstTime(processes, n);
    preemptiveSJF(processes, n);

    return 0;
}
