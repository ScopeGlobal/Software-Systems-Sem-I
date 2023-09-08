/*
============================================================================
Name : HOL21.c
Author : Sridhar Menon
Description : Write a program, call fork and print the parent and child process id.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {

	if (fork() == 0) {
		printf("Parent PID: %d\n", getppid());
		printf("Child PID: %d\n", getpid());
	}
	
	return 0;

}
