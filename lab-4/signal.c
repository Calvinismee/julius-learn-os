#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define SIGINT 2

/*
 Handler: If user input `Ctrl + C`, 
 foo function will be executed
*/

void foo(int sig) {
	printf("got signal %d\n", sig);
	/* 
	SIG_DFL will make signal handling back to default
	When clicking `Ctrl + C` for the first time, 
    		will exeucte `foo` first
	For the second time, it will close the program
		
	
	*/
	signal(SIGINT, SIG_DFL);
}

int main() {
	signal(SIGINT, foo);
	while(1) {
		puts("Hello");
		sleep(1);
	}
	return 0;
}
