#include <stdio.h>
#include <unistd.h>
#include <signal.h>


#define SIGTERM	15
int main() {
	pid_t child = fork();
	if (child == 0) {
		while(1) {
			puts("child");
			sleep(1);
		}
	} else {
		sleep(5);
		// Will kill the child after 5 secs
		kill(child, SIGTERM); 
	}
	return 0;
}
