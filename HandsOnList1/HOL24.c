/*
============================================================================
Name : HOL24.c
Author : Sridhar Menon
Description : Write a program to create an orphan process.
Date: 5th September, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(void) {

	if (fork() == 0) {
		printf("Child PID: %d", getpid());
		getchar();
	} else {
		printf("Parent PID: %d", getpid());
		exit(0);
	}
	
	return 0;

}
