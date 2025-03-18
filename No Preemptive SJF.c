/*#include <stdio.h>

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
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].waitTime, processes[i].turnAroundTime, processes[i].completionTime);
    }
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

void calculateWaitTimeNonPreemptive(Process processes[], int n) {
    processes[0].waitTime = 0;

    for (int i = 1; i < n; i++) {
        processes[i].waitTime = processes[i - 1].waitTime + processes[i - 1].burstTime;
    }
}

void calculateTurnAroundTimeNonPreemptive(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitTime;
        processes[i].completionTime = processes[i].arrivalTime + processes[i].turnAroundTime;
    }
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
    calculateWaitTimeNonPreemptive(processes, n);
    calculateTurnAroundTimeNonPreemptive(processes, n);
    printResults(processes, n);
    calculateAverageTimes(processes, n);

    return 0;
}
*/
#include <stdio.h>

typedef struct {
    int id;
    int burstTime;
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

void calculateWaitTimeNonPreemptive(Process processes[], int n) {
    int completed = 0, currentTime = 0;

    while (completed < n) {
        int minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].completionTime == 0) {
                if (minIndex == -1 || processes[i].burstTime < processes[minIndex].burstTime) {
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1) {

            currentTime += processes[minIndex].burstTime;
            processes[minIndex].completionTime = currentTime;


            processes[minIndex].turnAroundTime = processes[minIndex].completionTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;

            completed++;
        } else {

            currentTime++;
        }
    }
}

void printResults(Process processes[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].waitTime, processes[i].turnAroundTime, processes[i].completionTime);
    }
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
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);

        processes[i].completionTime = 0;
    }

    sortProcessesByArrivalAndBurstTime(processes, n);
    calculateWaitTimeNonPreemptive(processes, n);
    printResults(processes, n);
    calculateAverageTimes(processes, n);

    return 0;
}
