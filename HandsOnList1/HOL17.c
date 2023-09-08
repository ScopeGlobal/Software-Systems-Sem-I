/*
============================================================================
Name : HOL17.c
Author : Sridhar Menon
Description : Write a program to simulate online ticket reservation. Implement write lock 
Write a program to open a file, store a ticket number and exit. Write a separate program, to 
open the file, implement write lock, read the ticket number, increment the number and print 
the new ticket number then close the file
Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

	struct {
		int ticket_no;
	} data;
	
	struct flock lock;
	int fd = open("tickets.txt", O_RDWR);
	if (fd < 0) {
		perror("File opening failed ");
	}
	int reader = read(fd, &data, sizeof(data));
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	
	printf("We are about to enter the critical section \n");
	fcntl(fd, F_SETLKW, &lock);
	printf("Current ticket no is %d \n", data.ticket_no);
	lseek(fd, 0L, SEEK_SET);
	printf("We are now inside the critical section! \n");
	data.ticket_no++;
	write(fd, &data, sizeof(data));
	printf("Press any key to unlock!\n");
	getchar();
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("File Unlocked!\n");
	return 0;

}
