#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	
	pid = fork();
	
	if (pid == 0) {
    fork();
	} else if(pid > 0) {
		wait(NULL);
		puts("Child complete");
	}

  puts("child");
	return 0;
}
