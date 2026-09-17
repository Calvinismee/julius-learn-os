#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREAD 10



int sum;  // Shared data

// Thread will execute this :
void *runner(void *param) {
    int i, upper = atoi(param);
    sum = 0;

    for (i = 1; i <= upper; i++) {
        sum += i;
    }

    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t tid; // Thread id
    pthread_attr_t attr; // Attributes
    pthread_attr_init(&attr); // Set default attributes
    

    // Create new thread
    pthread_create(&tid, &attr, runner, argv[1]);

    // Parent will wait until created thread finish
    pthread_join(tid, NULL);
    printf("Sum: %d\n", sum);
}