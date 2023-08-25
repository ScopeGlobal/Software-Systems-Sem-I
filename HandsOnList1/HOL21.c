#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {

	if (fork() == 0) {
		printf("Parent PID: %d\n", getppid());
		printf("Child PID: %d\n", getpid());
	}
	
	return 0;

}
