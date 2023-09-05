#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int init_daemon(void) {

	if(!fork()) {
		setsid();
		chdir("/");
		umask(0);
		printf("%d \n", getpid());
		getchar();
		return 0;
	} else {
		exit(0);
	}
}

int main(void) {

	getchar();
	printf("Creating Daemon Process- \n");
	init_daemon();
	getchar();
	return 0;

}
