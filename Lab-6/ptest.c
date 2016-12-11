#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
	time_t ltime;

	while(1) {
		time(&ltime);
		printf("ptest: %s", ctime(&ltime));
		sleep(2);
	}

	exit(0);
}
