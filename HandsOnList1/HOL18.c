#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

struct {
	int train_num;
	int ticket_count;
} data;

int main(void) {

	int input;
	int fd = open("ticketrecord.txt", O_RDWR);
	printf("Select the number of the record to modify (1-5)- \n");
	scanf("%d", &input);
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (input - 1) * sizeof(data);
	lock.l_len = sizeof(data);
	lock.l_pid = getpid();
	
	lseek(fd, (input-1) * sizeof(data), SEEK_SET);
	read(fd, &data, sizeof(data));
	
	printf("We are about to enter the critical section! \n");
	
	fcntl(fd, F_SETLKW, &lock);
	printf("Ticket number: %d \n", data.ticket_count);
	data.ticket_count++;
	lseek(fd, -1 * sizeof(data), SEEK_CUR);
	write(fd, &data, sizeof(data));
	printf("To book ticket, press any key- \n");
	getchar();
	
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("Ticket booked!\n");
	return 0;	

}
