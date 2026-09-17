#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define SIGTERM	15
#define SIGCONT 18
#define SIGSTOP 19

int main() {
	pid_t child = fork();
	if (child == 0) {
		while(1) {
			puts("child");
			sleep(1);
		}
	} else {
		sleep(4);
		kill(child, SIGSTOP);
		puts("Waiting...");
		sleep(3);
		kill(child, SIGCONT);
		sleep(2);
		kill(child, SIGTERM);
		puts("Child is dead!");
	}
	return 0;
}
