#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

	struct {
		int ticket_no;
	} data;
	
	struct flock lock;
	int fd = open("ticket.txt", O_CREAT|O_RDWR);
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
	data.ticket_no++;
	lseek(fd, 0L, SEEK_SET);
	printf("We are now inside the critical section! \n");
	printf("Press any key to unlock!\n");
	getchar();
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("File Unlocked!\n");
	return 0;

}
