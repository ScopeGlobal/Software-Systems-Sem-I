  /*
============================================================================
Name : HOL19d.c
Author : Sridhar Menon
Description :  Create a FIFO file by
 d. mknod call

Date: 6th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(void) {

	int fifo_stat = mknod("fifofile6", S_IFIFO | 0666, 0);
	
	if (fifo_stat < 0) {
		perror("FIFO creation failed");
		return -1;
	}
	
	return 0;

}
