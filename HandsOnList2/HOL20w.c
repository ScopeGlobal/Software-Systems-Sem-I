#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(void) {

	mkfifo("fifofile3", 0666);
	
	int fd = open("fifofile5", O_RDWR);
	
	if (fd < 0) {
		perror("File opening failed");
		return -1;
	}
	
	char message[80];
	printf("Enter message to pass to FIFO: \n");
	scanf("%[^\n]", message);
	
	write(fd, message, sizeof(message));
	close(fd);
	
	return 0;
}
