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

int main(void) {

	fd_set rfds;
	struct timeval t;
	
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	t.tv_sec = 10;
	t.tv_usec = 0;
		
	int res = select(1, &rfds, NULL, NULL, &t);
	
	if (res == -1) {
		perror("Select failed : ");
	} else if (res == 1) {
		printf("Data received within 10s");
	} else {
		printf("Program Timed out!");
	}
	
	return res;
	
}
