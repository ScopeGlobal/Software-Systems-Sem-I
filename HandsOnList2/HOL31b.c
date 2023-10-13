#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
};

int main(void) {

	int sem_id;
	key_t key = ftok(".", 24);
	
	sem_id = semget(key, 1 , IPC_CREAT | 0666);
	if (sem_id < 0) {
		perror("Semaphore creation failed");
		return -1;
	}
	
	union semun sem_val;
	sem_val.val = 5;
	int set_semval = semctl(sem_id, 0, SETVAL, sem_val);
	
	if (set_semval < 0) {
		perror("Semaphore initialization failed");
		return -1;
	}	
	
	printf("Counting Semaphore initialized \n");
	return 0;

}
