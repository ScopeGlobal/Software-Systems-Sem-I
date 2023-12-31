/*
============================================================================
Name : HOL17a.c
Author : Sridhar Menon
Description : . Write a program to simulate online ticket reservation. Implement write lock 
Write a program to open a file, store a ticket number and exit. Write a separate program, to 
open the file, implement write lock, read the ticket number, increment the number and print 
the new ticket number then close the file.

Adding records

Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

	struct {
		int ticket_counter;
	} data;
	
	data.ticket_counter = 0;
	
	int fd = open("tickets.txt", O_CREAT|O_RDWR);
	if (fd < 0) {
		perror("File Opening failed ");
		return -1;
	}
	int writetest = write(fd, &data, sizeof(data));
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
