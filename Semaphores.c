#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buffer;
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer = i;
        printf("Producer produced: %d\n", buffer);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        printf("Consumer consumed: %d\n", buffer);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
