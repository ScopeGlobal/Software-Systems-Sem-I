/*
============================================================================
Name : HOL25.c
Author : Sridhar Menon
Description : Write a program to create three child processes. The parent should wait for a particular child (use 
waitpid system call).
Date: 5th September, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void) {

	if (fork() == 0) {
	
		if (fork() == 0) {
		
			printf("I am the third child! My PID is: %d \n", getpid());
			printf("Exiting...\n");
			exit(45);
		
		} else {
			int wstatus2;
			int process = waitpid(-1, &wstatus2, WEXITSTATUS(wstatus2));
			printf("Process %d exited normally!\n", process);
			printf("I am the first Child! My PID is: %d \n", getpid());
			printf("Child Execution complete! \n");
		}
		
	} else {
		int wstatus;	
		int process_changed = waitpid(-1, &wstatus, WEXITSTATUS(wstatus));
		printf("Process %d exited! \n", process_changed);
	
	}
	
	return 0;

}
