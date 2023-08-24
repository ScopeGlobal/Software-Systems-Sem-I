#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

	struct flock lock;
	int fd = open("lockfile2.txt", O_CREAT|O_RDWR);
	if (fd < 0) {
		perror("File Opening failed \n");
		return -1;
	}
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	printf("Attempting to Enter Critical Section now!\n");
	int locktest = fcntl(fd, F_SETLKW, &lock);
	if (locktest < 0) {
		perror("Locking failed \n");
		return -1;
	}
	printf("We are now inside the critical section!\n");
	printf("Press any key to unlock!\n");
	getchar();
	lock.l_type = F_UNLCK;
	int unlocktest = fcntl(fd, F_SETLK, &lock);
	if (unlocktest < 0) {
		perror("Unlock failed! \n");
		return -1;
	}
	printf("File Unlocked\n");
	return 0;
	
}
