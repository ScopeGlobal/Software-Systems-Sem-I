/*
============================================================================
Name : HOL1.c
Author : Sridhar Menon
Description : Create the following types of a files using (i) shell command (ii) system call
 a. soft link (symlink system call)
 b. hard link (link system call)
 c. FIFO (mkfifo Library Function or mknod system call)
Date: 11th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {

	int softL = symlink("tempfile.txt", "tempfileHL");
	if (softL < 0) {
		perror("Soft Link Creation failed ");
		return 1;
	}
	
	int hardL = link("tempfile.txt", "tempfileSL");
	if (hardL < 0) {
		perror("Hard Link Creation failed ");
		return 1;
	}
	
	int mkfifo = mknod("newfifopipe", S_IFIFO, 1);
	if (mkfifo < 0 ) {
		perror("FIFO Pipe Creation failed ");
		return 1;
	}
	
	return 0;
}
