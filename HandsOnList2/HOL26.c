/*
============================================================================
Name : HOL26.c
Author : Sridhar Menon
Description :  Write a program to send messages to the message queue. Check $ipcs -q

Date: 7th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[100];
};

int main() {
	key_t key = ftok(".", 24);
	int msgq;
	struct message msg;


	if (key < 0) {
		perror("key creation failed");
		return -1;
	}
	
	msgq = msgget(key, IPC_CREAT | 0666);
	
	if (msgq < 0) {
		perror("Message Queue Creation Failed");
		return -1;
	}

	msg.mtype = 1;
	 
	printf("Enter the Message to be sent: ");
	scanf("%[^\n]", msg.mtext);
	
	int msg_snd = msgsnd(msgq, &msg, sizeof(msg.mtext), 0);
	
	if (msg_snd < 0) {
		perror("Message sending failed");
		return -1;
	}

	return 0;
}

