#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t ptest_getPID();
int ptest_kill();
int ptest_run();
int ptest_restart();
void isRunning(int sig);

int main() {
	char command;

	(void) signal(SIGALRM, isRunning);
	alarm(5);
	
	while(1) {
		printf(">> ");
		command = getchar();
		fflush(stdin);
		switch(command) {
			case 'Q':
				printf("Good Bye\n");
				exit(0);
			case 'K':
				ptest_kill();
				break;
			case 'S':
				ptest_run();
				break;
			case 'R':
				ptest_restart();
				break;
		}
	}
	exit(0);
}

pid_t ptest_getPID() {
	FILE *fp;
	char buffer[100];
	int len;

	if((fp = popen("pidof ptest", "r")) == NULL)
		printf("Error\n");

	while((len = fscanf(fp, "%s", buffer)) > 0) {
		pclose(fp);
		return (pid_t)atoi(buffer);
	}

	pclose(fp);	
	return -1; 
}

int ptest_kill() {
	pid_t pid = ptest_getPID();

	if(pid == -1) {
		printf("No process to kill\n");
		return 0;
	} else {
		if(kill(pid, SIGTERM) == -1)
			kill(pid, SIGKILL);
		return 1;
	}
}

int ptest_run() {
	pid_t pid = ptest_getPID();

	if(pid != -1) {
		printf("already running\n");
		return 0;
	}

	char* ptest = "./ptest &";
	system(ptest);
	return 1;
}

int ptest_restart() {
	pid_t pid = ptest_getPID();
	if(pid == -1)
		printf("newly started\n");
	else
		ptest_kill();
	ptest_run();
}

void isRunning(int sig) {
	pid_t pid = ptest_getPID();
	if(pid != -1)
		printf("\npmon: running\n");
	else
		printf("\npmon: not existed\n");
	alarm(5);
}
