/*
============================================================================
Name : HOL6.c
Author : Sridhar Menon
Description : write a program to accept from STDIN and print to STDOUT. Use write and read only
Date: 18th Aug, 2023.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(void) {

	int fd;
	char buf[80];

	read(0, buf, sizeof(buf));
	perror("Status ");
	write(1, buf, sizeof(buf));
	perror("Status ");

}
