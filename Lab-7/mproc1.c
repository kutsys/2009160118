#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOTAL_PROC 10

int main () {
	pid_t pid[TOTAL_PROC];

	printf("2009160118 Lee Dong-Seok\n");

	for(int i=0; i<TOTAL_PROC; i++) {
		pid[i] = fork();
		
		if(pid[i] == 0) {
			printf("executing subproc, pid: %d\n", getpid());
			execl("./subproc", "subproc", NULL);
		}
	}

	// Wait for child process to finish
	for(int i=0; i<TOTAL_PROC; i++)
	wait(&pid[i]);

	printf("Finished (process)\n");	
	exit(0);
}
