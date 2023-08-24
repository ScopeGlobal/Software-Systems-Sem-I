#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/select.h>

int main(void) {

	fd_set rfds;
	struct timeval t;
	
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	t.tv_sec = 10;
	t.tv_usec = 0;
		
	int res = select(1, &rfds, NULL, NULL, &t);
	
	if (res == -1) {
		perror("Select failed : ");
	} else if (res == 1) {
		printf("Data received within 10s");
	} else {
		printf("Program Timed out!");
	}
	
	return res;
	
}
