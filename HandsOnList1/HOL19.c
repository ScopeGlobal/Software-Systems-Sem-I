#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(void) {

	struct timeval tstart, tstop;
	
	gettimeofday(&tstart, NULL);
	int pid = getpid();
	gettimeofday(&tstop, NULL);
	
	printf("Time taken to execute getpid() %ld \n", (tstop.tv_sec - tstart.tv_sec) * 100000 + (tstop.tv_usec - tstart.tv_usec));
	
	return 0;

}
