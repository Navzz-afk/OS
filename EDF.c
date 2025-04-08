#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

// Structure for each task
typedef struct {
    int task_id;          // Task ID
    int execution_time;   // Total execution time for the task
    int period;           // Period of the task
    int deadline;         // Deadline of the task
    int arrival_time;     // Arrival time (start time of task)
    int remaining_time;   // Remaining execution time
    int next_arrival_time; // Next time the task will arrive
} Task;

// Function to sort tasks based on their deadlines (Earliest Deadline First)
void sortTasksByDeadline(Task *tasks, int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].deadline > tasks[j].deadline) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

// Function to check if any task has arrived at the current time
void checkTaskArrival(Task *tasks, int n, int current_time) {
    for (int i = 0; i < n; i++) {
        if (tasks[i].next_arrival_time == current_time) {
            printf("Task %d has arrived at time %d\n", tasks[i].task_id, current_time);
        }
    }
}

// Function to find the highest priority task (earliest deadline) that is ready to execute
Task* getNextTask(Task *tasks, int n, int current_time) {
    Task *next_task = NULL;
    for (int i = 0; i < n; i++) {
        if (tasks[i].next_arrival_time <= current_time && tasks[i].remaining_time > 0) {
            if (next_task == NULL || tasks[i].deadline < next_task->deadline) {
                next_task = &tasks[i];
            }
        }
    }
    return next_task;
}

// Function to simulate the execution of tasks in the system using EDF
void scheduler(Task *tasks, int n, int total_time) {
    int current_time = 0;
    while (current_time < total_time) {
        // Check for new task arrivals
        checkTaskArrival(tasks, n, current_time);

        // Find the next task to execute based on earliest deadline
        Task *next_task = getNextTask(tasks, n, current_time);

        if (next_task != NULL) {
            // Execute the task
            printf("Executing Task %d at time %d\n", next_task->task_id, current_time);
            next_task->remaining_time--;

            // If task is completed, reschedule it
            if (next_task->remaining_time == 0) {
                next_task->next_arrival_time = current_time + next_task->period;  // Re-schedule
                next_task->remaining_time = next_task->execution_time;  // Reset remaining time for next period
                next_task->deadline = next_task->next_arrival_time;  // Update deadline for next period
                printf("Task %d completed and rescheduled at time %d\n", next_task->task_id, current_time);
            }
        } else {
            printf("Idle at time %d\n", current_time);  // CPU is idle if no task is ready
        }

        // Increment the time by one unit
        current_time++;
    }
}

// Function to input task details
void inputTasks(Task *tasks, int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter details for Task %d:\n", i + 1);
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Arrival time: ");
        scanf("%d", &tasks[i].arrival_time);

        // Calculate deadline (for simplicity, we assume deadline equals period)
        tasks[i].deadline = tasks[i].arrival_time + tasks[i].period;

        // Initialize remaining time and next arrival time
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_arrival_time = tasks[i].arrival_time;
        tasks[i].task_id = i + 1;  // Assign a unique task ID
    }
}

// Main function
int main() {
    int n;

    // Input number of tasks
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[MAX_TASKS];

    // Input task details
    inputTasks(tasks, n);

    // Sort tasks based on their deadlines (Earliest Deadline First)
    sortTasksByDeadline(tasks, n);

    // Simulate the scheduling for a given time frame
    int total_time = 100;  // Arbitrary total time for simulation (e.g., 100 units)

    // Call the scheduler function to manage the task execution
    scheduler(tasks, n, total_time);

    return 0;
}
