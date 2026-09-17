#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define SIGALRM 14

void ding(int sig) {
	puts("ding!");
}

int main() {
	pid_t child = fork();
	if (child == 0) {
		sleep(5);
		kill(child, SIGALRM);
	} else {
		signal(SIGALRM, ding);
		puts("waiting...");
		pause();
	}
	return 0;
}
