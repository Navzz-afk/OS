#include <stdio.h>

struct process {
    int process_id;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int rt;
};


void swap(struct process *a, struct process *b) {
    struct process temp = *a;
    *a = *b;
    *b = temp;
}


void sortByArrival(struct process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}


void calculateTimes(struct process processes[], int n) {
    sortByArrival(processes, n);
 float total_wt = 0, total_tat = 0, total_rt = 0;
   printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");

    processes[0].ct = processes[0].at + processes[0].bt;

        processes[0].tat = processes[0].ct - processes[0].at;
        processes[0].wt = processes[0].tat - processes[0].bt;
        processes[0].rt = processes[0].wt;
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
        processes[0].process_id, processes[0].at, processes[0].bt,
        processes[0].ct, processes[0].tat, processes[0].wt, processes[0].rt);

    for (int i = 1; i < n; i++) {
        if (processes[i - 1].ct < processes[i].at) {
            processes[i].ct = processes[i].at + processes[i].bt;
        } else {
            processes[i].ct = processes[i - 1].ct + processes[i].bt;
        }



        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        processes[i].rt = processes[i].wt;





        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
        processes[i].process_id, processes[i].at, processes[i].bt,
        processes[i].ct, processes[i].tat, processes[i].wt, processes[i].rt);

        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
        total_rt += processes[i].rt;
    }


    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

int main() {
    int n;


    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("\nEnter arrival timefor process %d: ", i + 1);
        scanf("%d", &processes[i].at);
        printf("\nEnter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].bt);
    }


    calculateTimes(processes, n);

    return 0;
}
