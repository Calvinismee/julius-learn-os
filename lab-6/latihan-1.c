#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 1000000
#define T 4

// Now we use mutex

int count = 0;

pthread_mutex_t mutex;

void* counting(void* arg) {
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < N / T; i++) count++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);

}

int main () {
    pthread_t t[T];
    int i;
   
    pthread_mutex_init(&mutex, NULL);
    for(i = 0; i < T; i++) {
        pthread_create(&t[i], NULL, counting, NULL);
    }

    for(i = 0; i < T; i++) pthread_join(t[i], NULL);
    printf("%d\n", count);
    pthread_mutex_destroy(&mutex);
    return 0;
}
