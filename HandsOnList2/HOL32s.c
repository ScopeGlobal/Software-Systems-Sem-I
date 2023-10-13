#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/sem.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
};

int main(void) {

	struct {
		int ticket_count;
	} data;
	
	union semun semarg;
	
	key_t key = ftok(".", 4);
	int semid = semget(key, 1, IPC_CREAT | 0666);
	if (semid < 0) {
		perror("Semaphore creation failed");
		return -1;
	}
	
	semarg.val = 1;
	// int sem_init = semctl(semid, 0, SETVAL, semarg);
	// if (sem_init < 0) {
	// 	perror("Semaphore initialization failed");
	// 	return -1;
	// }
	
	int fd = open("tickets.txt", O_RDWR);
	if (fd < 0) {
		perror("File Opening Failed");
		return -1;
	}
	
	int read_stat = read(fd, &data, sizeof(data));
	if (read_stat < 0) {
		perror("File Read failed");
		return -1;
	}
	
	printf("Current Ticket Count: %d \n", data.ticket_count);
	
	int current_sem_value = semctl(semid, 0, GETVAL, semarg);
	printf("Current Semaphore Value %d \n", current_sem_value);
	if (current_sem_value == -1) {
	    perror("Semaphore value retrieval failed");
	    return -1;
	}
	printf("Booking Ticket \n");
	struct sembuf buf = {0, -1, IPC_NOWAIT};
	semid = semget(key, 1, 0);
	int semset = semop(semid, &buf, 1);
	if (semset < 0) {
		perror("Semaphore locking failed");
		return -1;
	}
	
	current_sem_value = semctl(semid, 0, GETVAL, semarg);
	printf("Current Semaphore Value %d \n", current_sem_value);
	if (current_sem_value == -1) {
	    perror("Semaphore value retrieval failed");
	    return -1;
	}
	
	// CS
	printf("Inside CS \n");
	lseek(fd, 0L, SEEK_SET);
	data.ticket_count++;
	write(fd, &data, sizeof(data));
	printf("Press any key to unlock!\n");
	getchar();
	write(fd, &data, sizeof(data));
	// End of CS
	
	buf.sem_op = 1;
	int semreset = semop(semid, &buf, 1);
	if (semreset < 0) {
		perror("Semaphore Unlocking failed");
		return -1;
	}
	current_sem_value = semctl(semid, 0, GETVAL, semarg);
	printf("Current Semaphore Value %d \n", current_sem_value);
	if (current_sem_value == -1) {
	    perror("Semaphore value retrieval failed");
	    return -1;
	}
	
	printf("Ticket Booked \n");
	return 0;
		
}
