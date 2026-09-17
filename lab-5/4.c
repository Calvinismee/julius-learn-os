#include <stdio.h>
#include <pthread.h>
#define N 16
#define n 4

int sum = 0;

void* array_sum(void* arg) {
    // puts("Iamthread");
    int UPPER = N / n;
    for(int i = 0; i < UPPER; i++) {
        int el = ((int*) arg)[i];
        // printf("%d ", el);
        sum += el;
    }
    pthread_exit(NULL);
}

int main() {
    int A[N] = {68, 34, 64, 95, 35, 78, 65, 93,
                51, 67, 7, 77, 4, 73, 52, 91};
    pthread_t t[n];
    int i;
    for (i = 0; i < n; i++) {
        int div = (N * i) / n;
        pthread_create(&t[i], NULL, array_sum, &A[div]);
    }

    for (i = 0; i < n; i++) {
        pthread_join(t[i], NULL);
    }

    printf("%d\n", sum);    /* 954      */

    return 0;
}
