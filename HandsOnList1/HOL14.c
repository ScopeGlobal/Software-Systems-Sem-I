/*
============================================================================
Name : HOL14.c
Author : Sridhar Menon
Description : Write a program to find the type of a file.
 a. Input should be taken from command line.
 b. program should be able to identify any type of a file.
Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<time.h>

int main(int argc, char* argv[]) {

	struct stat st;
	
	if (argc != 2) {
		printf("Incorrect number of Arguments. Expected filepath");
		return -1;
	}
	
	int res = stat(argv[1], &st);
	
	if (res == -1) {
		perror("Stat() failed ");
		return -1;
	}
	
	printf("File type: %d", st.st_mode);
	return 0;
}
