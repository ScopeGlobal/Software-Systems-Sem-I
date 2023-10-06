#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void) {

	mkfifo("fifofile4", 0666);
	
	int fd = open("fifofile4", O_RDWR);
	
	if (fd < 0) {
		perror("File opening failed");
		return -1;
	}
	char received[80];
	
	read(fd, received, sizeof(received));
	
	printf("Received message %s", received);
	
	char message[80];
	
	printf("Enter message to be sent: ");
	scanf("%[^\n]", message);
	
	write(fd, message, sizeof(message));
	
	close(fd);
	
	return 0;
	
	
	
}
