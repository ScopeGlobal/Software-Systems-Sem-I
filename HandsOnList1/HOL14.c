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
	switch (st.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
	return 0;
}
