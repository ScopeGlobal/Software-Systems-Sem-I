/*
============================================================================
Name : HOL4.c
Author : Sridhar Menon
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 17th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
 
 int main(void) {
 	int fd;
 	char buf[80];
 	fd = open("tempfile.txt", O_RDWR|O_EXCL);
 	if (fd < 0) {
 		perror("Failed ");
 	}
 	printf("Enter text: ");
 	scanf("%[^\n]", buf);
 	write(fd, buf, sizeof(buf));
 	perror("Status ");
 	getchar();
 }
