#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#define SIGINT 2

void foo(int sign) {
    printf("Signal : %d\n", sign);
    signal(sign, foo);
}   

int main () {
    signal(SIGINT, foo);
    while(1) {
        puts("n");
        sleep(1);

    }
	return 0;
}
