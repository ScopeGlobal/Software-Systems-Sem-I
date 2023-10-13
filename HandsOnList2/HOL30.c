#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

int main(void) {

	int key = ftok(".", 24);

	int shm = shmget(key, 1024, IPC_CREAT | 0666);
	if (shm < 0) {
		perror("Shared Memory creation failed");
		return -1;
	}
	
	char *shm_write = (char *)shmat(shm, NULL, 0);
	printf("Enter what you want to write: ");
	scanf("%[^\n]", shm_write);
	
	int shm_detach_1 = shmdt(shm_write);
	if (shm_detach_1 < 0) {
		perror("Detach Failed");
		return -1;
	}
	
	// O_RDONLY attach
	shm_write = (char *)shmat(shm, NULL, SHM_RDONLY);
	printf("Enter what you want to write: ");
	scanf("%[^\n]", shm_write);
	
	int shm_detach_2 = shmdt(shm_write);
	if (shm_detach_2 < 0) {
		perror("Detach 2 Failed");
		return -1;
	}
	
	int shm_rm = shmctl(shm, IPC_RMID, NULL);
	if (shm_rm < 0) {
		perror("Removing Shared Memory Failed");
		return -1;
	}
	
	return 0;

}
