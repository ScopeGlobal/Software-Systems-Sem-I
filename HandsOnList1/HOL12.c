/*
============================================================================
Name : HOL12.c
Author : Sridhar Menon
Description : write a program to determine the opening mode of a file using fcntl
Date: 24th Aug, 2023.
============================================================================
*/

#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main(void) {

	int fd = open("dupfile.txt", O_RDWR);
	if (fd < 0) {
		perror("File opening failed ");
	}
	printf("F_GETFD %d \n", fcntl(fd, F_GETFD));
	printf("F_GETFL %d \n", fcntl(fd, F_GETFL));
	
	switch (fcntl(fd, F_GETFL)) {
		case 32770: printf("O_RDWR"); break;
		case 32768: printf("O_RDONLY"); break;
		case 32769: printf("O_WRONLY"); break;
		default: printf("Invalid");
	
	}
	return 0;
}
