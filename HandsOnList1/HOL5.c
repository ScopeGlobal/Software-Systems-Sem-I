// write a program to create 5 new files with infinite loop. Execute program in background and check the file descriptor table

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void) {

	int fd1 = open("tempfile1.txt", O_CREAT|O_RDWR);
	if (fd1 < 0) {
		perror("Status ");
	}
	int fd2 = open("tempfile2.txt", O_CREAT|O_RDWR);
	if (fd2 < 0) {
		perror("Status ");
	}
	int fd3 = open("tempfile3.txt", O_CREAT|O_RDWR);
	if (fd3 < 0) {
		perror("Status ");
	}
	int fd4 = open("tempfile4.txt", O_CREAT|O_RDWR);
	if (fd4 < 0) {
		perror("Status ");
	}
	int fd5 = open("tempfile5.txt", O_CREAT|O_RDWR);
	if (fd5 < 0) {
		perror("Status ");
	}
	getchar();

} 
