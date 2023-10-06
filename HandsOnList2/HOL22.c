/*
============================================================================
Name : HOL13.c
Author : Sridhar Menon
Description :  Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to 
verify whether the data is available within 10 seconds or not (check in $man 2 select)
Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/time.h>

int main(void) {

	fd_set rfds;
	struct timeval t;
	
	mkfifo("fifofile5", 0666);
	int fd = open("fifofile5", O_RDWR);
	
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	t.tv_sec = 10;
	t.tv_usec = 0;
		
	int res = select(fd + 1, &rfds, NULL, NULL, &t);
	
	if (res == -1) {
		perror("Select failed : ");
	} else if (res == 1) {
		char message[80];
		read(fd, message, sizeof(message));
		printf("Message received: %s", message);
	} else {
		printf("Program Timed out!");
	}
	
	return res;
	
}
