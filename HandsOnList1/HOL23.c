/*
============================================================================
Name : HOL23.c
Author : Sridhar Menon
Description :  Write a program to create a Zombie state of the running program
Date: 5th September, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {

	if (fork() == 0) {
		printf("Child PID: %d\n", getpid());
		exit(0);
	} else {
		printf("Parent PID: %d\n", getpid());
		getchar();
	}
	return 0;
}
