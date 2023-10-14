/*
============================================================================
Name : HOL29.c
Author : Sridhar Menon
Description :   Write a program to remove the message queue.

Date: 7th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(void) {

	key_t key = ftok(".", 24);
	if (key < 0) {
		perror("Key generation failed");
		return -1;
	}
	
	int msgq = msgget(key, IPC_CREAT | 0666);
	if (msgq < 0) {
		perror("Message Queue Creation failed");
		return -1;
	}
	
	printf("Message Queue generated under key %d \n", key);
	printf("Message Queue ID: %d \n", msgq);
	
	int msg_rm = msgctl(msgq, IPC_RMID, NULL);
	if (msg_rm < 0) {
		perror("Message Queue removal failed");
		return -1;
	}
	
	printf("Message Queue removed successfully \n");
	
	return 0;

}
