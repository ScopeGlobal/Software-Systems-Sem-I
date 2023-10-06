#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(void) {

	int fifo_stat = mkfifo("fifofile2", 0666);
	
	if (fifo_stat < 0) {
		perror("FIFO creation failed");
		return -1;
	}
	
	return 0;

}
