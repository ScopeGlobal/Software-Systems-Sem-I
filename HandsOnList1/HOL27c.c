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
