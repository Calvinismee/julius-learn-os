#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
    pid_t pid = fork();

    if(pid == 0) {
        while(1) {
            puts("child");
            sleep(1);
        }
    }
	return 0;
}
