/*
============================================================================
Name : HOL27c.c
Author : Sridhar Menon
Description : 7. Write a program to execute ls -Rl by the following system calls
 b. execle
Date: 5th September, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
extern char **environ;
int main(void) {
	char *const envp[80];
	int process_execution_status = execle("/bin/ls", "-R", "-l", (char *) NULL, envp);
	if (process_execution_status < 0) {
		perror("execl() failed");
		return -1;
	} 
	return 0;

}
