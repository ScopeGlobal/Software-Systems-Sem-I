 /*
============================================================================
Name : HOL16.c
Author : Sridhar Menon
Description : Write a program to send and receive data from parent to child vice versa. Use two way 
communication
Date: 6th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void) {

	char buf[80];
	char bufresponse[80];
	int pipefd[2];
	int pipefd1[2];
	
	if (pipe(pipefd) == -1) {
		perror("Pipe 1 Error");
		return -1;
	}
	if (pipe(pipefd1) == -1) {
		perror("Pipe 2 Error");
		return -1;
	}
	
	if (!fork()) {
		close(pipefd[1]);
		close(pipefd1[0]);
		read(pipefd[0], buf, sizeof(buf));
		printf("Message from Parent: %s \n", buf);
		printf("Enter Child's response - \n");
		scanf("%[^\n]", bufresponse);
		write(pipefd1[1], bufresponse, sizeof(bufresponse));
		close(pipefd[0]);
		close(pipefd1[1]);
		exit(0);
	} else {
		close(pipefd[0]);
		close(pipefd1[1]);
		printf("Enter the message to be sent to the child- \n");
		scanf("%[^\n]", buf);
		write(pipefd[1], buf, sizeof(buf));
		read(pipefd1[0], bufresponse, sizeof(bufresponse));
		printf("Child's response - %s", bufresponse);
		close(pipefd[1]);
		close(pipefd1[0]);
		wait(NULL);
		exit(0);
	}

}
