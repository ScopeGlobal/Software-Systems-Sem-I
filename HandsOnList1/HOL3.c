/*
============================================================================
Name : HOL3.c
Author : Sridhar Menon
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 11th Aug, 2023.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {

	int fd1 = creat("HOL3file1.txt", O_RDWR);
	int fd2 = creat("HOL3file2.txt", O_RDWR);
	int fd3 = creat("HOL3file3.txt", O_RDWR);
	int fd4 = creat("HOL3file4.txt", O_RDWR);
	int fd5 = creat("HOL3file5.txt", O_RDWR);
	
	printf("File descriptors are: %d %d %d %d %d", fd1, fd2, fd3, fd4, fd5);
	
	return 0;
	
}
