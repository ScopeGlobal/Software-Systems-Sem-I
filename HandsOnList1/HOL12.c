// write a program to determine the opening mode of a file using fcntl

#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main(void) {

	int fd = open("dupfile.txt", O_RDWR);
	if (fd < 0) {
		perror("File opening failed ");
	}
	printf("F_GETFD %d", fcntl(fd, F_GETFD));
	printf("F_GETFL %d", fcntl(fd, F_GETFL));
	return 0;
}
