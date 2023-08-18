// write a program to accept from STDIN and print to STDOUT. Use write and read only

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(void) {

	int fd;
	char buf[80];

	read(0, buf, sizeof(buf));
	perror("Status ");
	write(1, buf, sizeof(buf));
	perror("Status ");

}
