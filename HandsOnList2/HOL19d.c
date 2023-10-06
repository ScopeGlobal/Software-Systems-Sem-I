#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(void) {

	int fifo_stat = mknod("fifofile", S_IFIFO | 0666, 0);
	
	if (fifo_stat < 0) {
		perror("FIFO creation failed");
		return -1;
	}
	
	return 0;

}
