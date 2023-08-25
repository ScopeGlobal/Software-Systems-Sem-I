#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {

	if (fork() == 0) {
		printf("Child PID: %d\n", getpid());
	} else {
		printf("Parent PID: %d\n", getpid());
	}
	sleep(20);
	return 0;
}
