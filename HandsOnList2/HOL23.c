#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>

int main(void) {

	struct rlimit lim;
	
	int rlim_stat = getrlimit(RLIMIT_NOFILE, &lim);
	
	if (rlim_stat < 0) {
		perror("getrlimit failed");
		return -1;
	} else {
		printf("Max no of files opened in a process- %ld \n", lim.rlim_cur);
	}
	
	long PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
	printf("Max data written to pipe- %ld \n", PIPE_BUF);
	
	return 0;

}
