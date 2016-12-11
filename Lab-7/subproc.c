#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0;
int test_funct() {
	time_t ltime;
	struct tm *ts;

	ltime = time(NULL);
	ts = localtime(&ltime);
	srand(ltime);

	int r = rand()%10;
	sleep(r);
	printf("pid : %d, count : %d, ", getpid(), count);
	printf("Local Time : %4d-%2d-%2d %2d:%2d:%2d\n", ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec);
	return ++count;
}

int main () {
	while(test_funct() <= 20) {
		test_funct();
	}

	exit(0);
}
