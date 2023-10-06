#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void) {

	char buf[80];
	int pipefd[2];
	
	if (pipe(pipefd) == -1) {
		perror("Pipe Error");
		return -1;
	}
	
	if (!fork()) {
		close(pipefd[1]);
		read(pipefd[0], buf, sizeof(buf));
		printf("Message from Parent: %s", buf);
		close(pipefd[0]);
		exit(0);
	} else {
		close(pipefd[0]);
		printf("Enter the message to be sent to the child- \n");
		scanf("%[^\n]", buf);
		write(pipefd[1], buf, sizeof(buf));
		close(pipefd[1]);
		wait(NULL);
		exit(0);
	}

}
