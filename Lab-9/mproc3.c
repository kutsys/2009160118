#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define TOTAL_THREAD 10

pthread_mutex_t mymutex;
int count = 0;

void* thread_function(void *arg) {
	int r;
	time_t ltime;
	struct tm *ts;


	while(1) {
		ltime = time(NULL);
		ts = localtime(&ltime);
		srand(ltime);

		pthread_mutex_lock(&mymutex);
		printf("Thread: %d, Count : %d, ",(int)pthread_self() ,++count);
		printf("Local Time : %4d-%2d-%2d %2d:%2d:%2d\n", ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec);
		pthread_mutex_unlock(&mymutex);

		r = rand()%10;
		sleep(r);
		
		if(count == 20)
			break;
	}
}

int main () {
	int res;
	pthread_t threads[TOTAL_THREAD];
	pthread_mutex_init(&mymutex, NULL);
	void *thread_result;

	printf("2009160118 Lee Dong-Seok\n");

	for(int i=0; i<TOTAL_THREAD; i++) {
		printf("Creating Thread.\n");
		res = pthread_create(&threads[i], NULL, thread_function, NULL);
		
		if(res != 0) {
			printf("Thread creation failed.\n");
			exit(EXIT_FAILURE);
		}
	}

	for(int i=0; i<TOTAL_THREAD; i++) {
		res = pthread_join(threads[i], &thread_result);
		
		if(res == 0) {
			printf("Thread Joined.\n");
		} else {
			printf("Thread join failed.\n");
			exit(EXIT_FAILURE);
		}
	}

	pthread_mutex_destroy(&mymutex);
	printf("Finished Successfully\n");	
	exit(EXIT_SUCCESS);
}
