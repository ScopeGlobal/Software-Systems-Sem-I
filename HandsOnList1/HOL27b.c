/*
============================================================================
Name : HOL27b.c
Author : Sridhar Menon
Description : 7. Write a program to execute ls -Rl by the following system calls
 b. execlp
Date: 5th September, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(void) {

	int process_execution_status = execlp("ls", "-R", "-l", (char *) NULL);
	if (process_execution_status < 0) {
		perror("execl() failed");
		return -1;
	} 
	return 0;

}
