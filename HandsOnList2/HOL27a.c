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

	if (msgrcv(msgq, &msg, sizeof(msg.mtext), 1, 0) == -1) {
		perror("msgrcv failed");
		exit(1);
	}

	printf("Received message : %s\n", msg.mtext);


	return 0;
}

