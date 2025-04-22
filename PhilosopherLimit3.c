#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PHILOSOPHERS 5
#define MEALS 3  

pthread_mutex_t forks[PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % PHILOSOPHERS;

    for (int i = 0; i < MEALS; i++) {
       
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);

        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        } else {
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }

       
        printf("Philosopher %d is eating meal %d.\n", id, i + 1);
        sleep(1);

       
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
    }

    printf("Philosopher %d has finished all meals and leaves the table.\n", id);
    return NULL;
}

int main() {
    pthread_t threads[PHILOSOPHERS];
    int ids[PHILOSOPHERS];

   
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

   
    for (int i = 0; i < PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

  
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    printf("Dinner is over. All philosophers have left the table.\n");
    return 0;
}
