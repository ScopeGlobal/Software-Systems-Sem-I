/*
============================================================================
Name : HOL27d.c
Author : Sridhar Menon
Description : 7. Write a program to execute ls -Rl by the following system calls
 b. execv
Date: 5th September, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(void) {

	char* const argv[3] = {"-R", "-l", (char *) NULL};

	int process_execution_status = execv("/bin/ls", argv);
	if (process_execution_status < 0) {
		perror("execl() failed");
		return -1;
	} 
	return 0;

}
