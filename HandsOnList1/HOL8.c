/*
============================================================================
Name : HOL8.c
Author : Sridhar Menon
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read. 
Close the file when end of file is reached.
Date: 18th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Incorrect number of Arguments!");
	}
	
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("Failed ");
	}
	int end_file = 0;
	while (!end_file) {
		char buf;
		while (1) {
			int read_res = read(fd, &buf, 1);
			if (read_res == 0) {
				end_file = 1;
				int close_fd = close(fd);
				if (close_fd < 0) {
					perror("Closing Failure ");
				}
				break;
			}
			printf("%c", buf);
			if (buf == '\n') {
				break;
			}
		}
	}
	return 0;
}
