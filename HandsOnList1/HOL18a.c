/*
============================================================================
Name : HOL18a.c
Author : Sridhar Menon
Description :Write a program to perform Record locking.
 a. Implement write lock
 b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access 
to avoid race condition.

Adding Records
Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

	struct {
		int train_no;
		int ticket_counter;
	} data[5];
	
	for(int i = 0; i < 5; i++) {
		data[i].train_no = i + 1;
		data[i].ticket_counter = 0;
	}
	
	int fd = open("ticketrecord.txt", O_CREAT|O_RDWR);
	if (fd < 0) {
		perror("File Opening failed ");
		return -1;
	}
	int writetest = write(fd, data, sizeof(data));
	if (writetest < 0) {
		perror("Write failed ");
		return -1;
	}
	
	int closetest = close(fd);
	if (closetest < 0) {
		perror("File closing failed ");
		return -1;
	}
	return 0;
}
