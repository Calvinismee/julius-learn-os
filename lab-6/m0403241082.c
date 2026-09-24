#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 100000
#define T 4

pthread_mutex_t mutex;

int sum = 0;

void* array_sum(void* arg) {
    pthread_mutex_lock(&mutex);
    int *A = (int*)arg;

    for (int i = 0; i < N/T; i++)
        sum += A[i];

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main () {
    pthread_t t[T];
    int A[N], i;
    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < N; i++) 
        A[i] = rand()%10;

    for(i = 0; i < T; i++) 
        pthread_create(&t[i], NULL, array_sum, &A[i*N/T]);

    for(i = 0; i < T; i++)
        pthread_join(t[i], NULL);

    printf("%d\n", sum);
    pthread_mutex_destroy(&mutex);
    return 0;
}
