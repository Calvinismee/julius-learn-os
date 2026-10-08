#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
    pid_t pid;
    char* msg;
    int n;

    pid = fork();

    if(pid == 0) {
        msg = "child";
        n = 8;
    } else {
        msg = "parent";
        n = 3;
    }

    while(n--) {
        puts(msg);
        sleep(1);
    }
    
	return 0;
}
