/*
============================================================================
Name : HOL11b.c
Author : Sridhar Menon
Description :  Write a program to open a file, duplicate the file descriptor and append the file with both the 
descriptors and check whether the file is updated properly or not.
b. use dup2
Date: 24th Aug, 2023.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(void) {

	char buf[80];
	
	int fd1 = open("dupfile2.txt", O_CREAT|O_RDWR);
	int fd2;
	
	int fd2_status = dup2(fd1, fd2);
	if (fd2_status < 0) {
		perror("Duplication failed ");
	}
	printf("Enter text: ");
	scanf("%[^\n]", buf);
	int fd1_write = write(fd1, buf, sizeof(buf));
	if (fd1_write < 0) {
		perror("fd1 write failed ");
		return -1;
	}
	
	int fd2_write = write(fd2, buf, sizeof(buf));
	if (fd2_write < 0) {
		perror("fd2 write failed ");
		return -1;
	}
	
	int fd1_close = close(fd1);
	if (fd1_close < 0) {
		perror("Closing fd1 failed ");
		return -1;
	}
	int fd2_close = close(fd2);
	if (fd2_close < 0) {
		perror("Closing fd2 failed");
		return -1;
	}
	
	return 0;
}
