#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main () {
    pid_t pid;
    char* msg;
    int n;

    pid = fork();

    if(pid == 0) {
        msg = "child";
        n = 4;
    } else {
        msg = "parent";
        n = 10;
    }


    while(n--) {
        puts(msg);
        sleep(1);
    }
    
    if(pid > 0) {
        int status;
        wait(&status);
        printf("%d", WEXITSTATUS(status));
    }

    
	return 0;
}
