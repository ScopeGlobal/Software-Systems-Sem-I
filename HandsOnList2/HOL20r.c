  /*
============================================================================
Name : HOL20.c
Author : Sridhar Menon
Description :  Write two programs so that both can communicate by FIFO -Use one way communication.

Date: 6th Oct, 2023.
============================================================================
*/


#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(void) {

	mkfifo("fifofile3", 0666);
	
	int fd = open("fifofile3", O_RDWR);
	
	if (fd < 0) {
		perror("File opening failed");
		return -1;
	}
	
	char message[80];
	
	read(fd, message, sizeof(message));
	close(fd);
	
	printf("Received %s", message);
	return 0;
}
