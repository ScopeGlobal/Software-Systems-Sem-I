/*
============================================================================
Name : HOL27b.c
Author : Sridhar Menon
Description :   Write a program to receive messages from the message queue.
 a. with IPC_NOWAIT as a flag

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
	key_t key;
	int msgq;
	struct message msg;

	key = ftok(".", 24);
	if (key < 0) {
		perror("ftok");
		return -1;
	}
	msgq = msgget(key, 0666);
	if (msgq < 0) {
		perror("msgget");
		exit(1);
	}

	if (msgrcv(msgq, &msg, sizeof(msg.mtext), 1, IPC_NOWAIT) == -1) {
		perror("msgrcv failed");
		exit(1);
	} else {
		printf("Received message: %s\n", msg.mtext);
	}


	return 0;
}

