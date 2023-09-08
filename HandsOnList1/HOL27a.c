/*
============================================================================
Name : HOL27a.c
Author : Sridhar Menon
Description : 7. Write a program to execute ls -Rl by the following system calls
 a. execl
Date: 5th Spetember, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(void) {

	int process_execution_status = execl("/bin/ls", "-R", "-l", (char *) NULL);
	if (process_execution_status < 0) {
		perror("execl() failed");
		return -1;
	} 
	return 0;

}
