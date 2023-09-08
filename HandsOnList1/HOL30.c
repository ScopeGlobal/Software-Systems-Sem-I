/*
============================================================================
Name : HOL30.c
Author : Sridhar Menon
Description : Write a program to run a script at a specific time using a Daemon process
Date: 5th September, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int init_daemon(void) {

	if(!fork()) {
		setsid();
		chdir("/");
		umask(0);
		printf("%d \n", getpid());
		getchar();
		return 0;
	} else {
		exit(0);
	}
}

int main(void) {

	getchar();
	printf("Creating Daemon Process- \n");
	init_daemon();
	getchar();
	return 0;

}
