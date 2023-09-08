/*
============================================================================
Name : HOL10.c
Author : Sridhar Menon
Description :  Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 
bytes (use lseek) and write again 10 bytes. 
 a. check the return value of lseek
 b. open the file with od and check the empty spaces in between the data.
Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void) {

	int fd = open("testfile.txt", O_CREAT|O_RDWR);
	if (fd < 0) {
		perror("Opening Failed ");
		return -1;
	}
	char buf[80];
	printf("Enter text: ");
	scanf("%[^\n]", buf);
	
	int fd_write = write(fd, buf, 10);
	if (fd_write < 0) {
		perror("Write failed! ");
		return -1;
	}
	
	int fd_lseek = lseek(fd, 10L, SEEK_CUR);
	if (fd_lseek < 0) {
		perror("Lseek failed ");
		return -1;
	}
	int fd_write2 = write(fd, buf, 10);
	if (fd_write2 < 0) {
		perror("2nd write failed! ");
		return -1;
	}
	
	return 0;
	

}
