#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define N 1000000
#define T 4

// Now we use semaphore

int count = 0;

sem_t sem;

void* counting(void* arg) {
    sem_wait(&sem);
    for(int i = 0; i < N / T; i++) count++;
    sem_post(&sem);
    pthread_exit(NULL);
}

int main () {
    pthread_t t[T];
    int i;
    
    sem_init(&sem, 0, 1);
    for(i = 0; i < T; i++) {
        pthread_create(&t[i], NULL, counting, NULL);
    }

    for(i = 0; i < T; i++) pthread_join(t[i], NULL);
    printf("%d\n", count);
    sem_destroy(&sem);
    return 0;
}
