#include<stdio.h>
#include<unistd.h>

int main(void) {

	int process_execution_status = execlp("ls", "-R", "-l", (char *) NULL);
	if (process_execution_status < 0) {
		perror("execl() failed");
		return -1;
	} 
	return 0;

}
