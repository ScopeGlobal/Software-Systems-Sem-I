 /*
============================================================================
Name : HOL17c.c
Author : Sridhar Menon
Description : Write a program to execute ls -l | wc.
 a. use fcntl
Date: 6th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(void) {

	int pipefd[2];
	
	int pipe_stat = pipe(pipefd);
	
	if (pipe_stat < 0) {
		perror("Pipe Failed");
		exit(-1);
	}
	
	if (fork() == 0) {
	
		close(pipefd[0]);
		close(1);
		int fcntl_status = fcntl(pipefd[1], F_DUPFD, 1);
		close(pipefd[1]);
		
		execlp("ls", "ls", "-l", (char*) NULL);
		perror("Exec failed");
		exit(-1);
	
	} else {
	
		close(pipefd[1]);
		close(0);
		int fcntl_status_2 = fcntl(pipefd[0], F_DUPFD, 0);
		if (fcntl_status_2 < 0) {
			perror("fcntl fail");
		}
		close(pipefd[0]);
		
		execlp("wc", "wc", (char *) NULL);
		perror("Parent Exec Failed");
		exit(-1);
	
	}
	
	return 0;

}
