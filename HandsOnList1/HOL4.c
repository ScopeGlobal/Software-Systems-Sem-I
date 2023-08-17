// write a program to open an existing file in Read/Write mode. Try O_EXCL flag also

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
 
 int main(void) {
 	int fd;
 	char buf[80];
 	fd = open("tempfile.txt", O_RDWR|O_EXCL);
 	if (fd < 0) {
 		perror("Failed ");
 	}
 	printf("Enter text: ");
 	scanf("%[^\n]", buf);
 	write(fd, buf, sizeof(buf));
 	perror("Status ");
 	getchar();
 }
