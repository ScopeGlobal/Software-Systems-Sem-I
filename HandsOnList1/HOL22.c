#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>

int main(void) {

	int fd = open("forkfile.txt", O_CREAT|O_RDWR);
	char str[] = "Hi this is Me!";
	
	if(fork() == 0) {
		int write_test = write(fd, &str, sizeof(str));
		if (write_test < 0) {
			perror("Child Write Failed! ");
			return -1;
		}
	} else {
		int write_test_2 = write(fd, &str, sizeof(str));
		if (write_test_2 < 0) {
			perror("Parent Write Failed! ");
			return -1;
		}
	}
	return 0;
}
