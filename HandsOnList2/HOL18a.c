  /*
============================================================================
Name : HOL18.c
Author : Sridhar Menon
Description :  Write a program to find out total number of directories on the pwd.
 execute ls -l | grep ^d | wc ? Use only dup2.
Date: 6th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void) {

	int pipefd1[2];
	pipe(pipefd1);
	
	if (fork() == 0) {
	
		dup2(pipefd1[1], 1);
		close(pipefd1[0]);
		execlp("ls", "ls", "-l", (char *) NULL);

	} else {
		int pipefd2[2];
		pipe(pipefd2);
		dup2(pipefd1[0], 0);
		close(pipefd1[1]);
		
		if (fork() == 0) {
			dup2(pipefd2[1], 1);
			close(pipefd2[0]);
			execlp("grep", "grep", "^d", (char *) NULL);
		} else {
			dup2(pipefd2[0], 0);
			close(pipefd2[1]);
			execlp("wc", "wc", (char *) NULL);
		}
	}
	return 0;
}
