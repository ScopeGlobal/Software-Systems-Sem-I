#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(void) {

	key_t key;
	int msgq;
	
	key = ftok(".", 66);
	
	if (key < 0) {
		perror("Key generation failed");
		return -1;
	} 
	
	msgq = msgget(key, IPC_CREAT | 0666);
	
	if (msgq < 0) {
		perror("Message Queue creation failed");
		return -1;
	}
	
	printf("ID of message queue: %d \n", msgq);
	
	return 0;
	
}
