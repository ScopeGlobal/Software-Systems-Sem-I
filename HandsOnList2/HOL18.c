#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void) {

	int pipefd1[2];
	int pipefd2[2];
	
	int pipe_stat1 = pipe(pipefd1);
	int pipe_stat2 = pipe(pipefd2);
	
	if (pipe_stat1 < 0) {
		perror("Pipe 1 failed");
		exit(-1);
	}
	
	if (pipe_stat2 < 0) {
		perror("Pipe 2 failed");
		exit(-1);
	}
	
	int ls_pid = fork();
	if (ls_pid == 0) {

		close(pipefd1[0]);
		close(1);
		
		dup2(pipefd1[1], 1);
		close(pipefd1[1]);
		
		execlp("ls", "ls", "-l", (char *) NULL);
		perror("Exec for ls failed");
		return -1;
	} else {
		int grep_pid = fork();
		if (grep_pid == 0) {
		
			
		
			close(pipefd1[1]);
			close(pipefd2[0]);
			close(0);
			
			dup2(pipefd1[0], 0);
			close(pipefd1[0]);
			close(1);
			
			dup2(pipefd2[1], 1);
			close(pipefd2[1]);
			
			execlp("grep", "grep", "^d", (char *) NULL);
			perror("Exec for Grep failed");
			return -1;
		
		} else {
		
			close(pipefd2[1]);
			close(0);
			
			dup2(pipefd2[0], 0);
			close(pipefd2[0]);
			
			execlp("wc", "wc", (char *) NULL);
			perror("exec for wc failed");
			return -1;
		
		}
	}
	return 0;
}
