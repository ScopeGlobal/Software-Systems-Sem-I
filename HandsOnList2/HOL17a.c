#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

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
		int fd2 = dup(pipefd[1]);
		close(pipefd[1]);
		
		execlp("ls", "ls", "-l", (char*) NULL);
		perror("Exec failed");
		exit(-1);
	
	} else {
	
		close(pipefd[1]);
		close(0);
		int fd3 = dup(pipefd[0]);
		close(pipefd[0]);
		
		execlp("wc", "wc", (char *) NULL);
		perror("Parent Exec Failed");
		exit(-1);
	
	}
	
	return 0;

}
