#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>

int main(void) {

	key_t key = ftok(".", 23);
	
	if (key < 0 ) {
		perror("Key generation failed");
		return -1;
	}
	
	int msgq = msgget(key, IPC_CREAT | 0666);
	
	if (msgq < 0) {
		perror("Message Queue Creation failed");
		return -1;
	}
	
	struct msqid_ds msq_info;
	
	int msqds_stat = msgctl(msgq, IPC_STAT, &msq_info);
	
	if (msqds_stat < 0) {
		perror("Stat retrieval failed");
		return -1;
	}
	
	printf("Access Permissions: %o \n", msq_info.msg_perm.mode);
	printf("UID: %d \n", msq_info.msg_perm.uid);
	printf("GID: %d \n", msq_info.msg_perm.gid);
	printf("Last message send time: %s \n", ctime(&msq_info.msg_stime));
	printf("Last message receiving time: %s \n", ctime(&msq_info.msg_rtime));
	printf("Last Change time: %s \n", ctime(&msq_info.msg_ctime));
	printf("Size of queue: %lu \n", msq_info.msg_qbytes);
	printf("Number of messages in the queue: %lu \n", msq_info.msg_qnum);
	printf("Maximum number of bytes allowed: %lu \n", msq_info.msg_qbytes);
	printf("PID of msgsnd: %d \n", msq_info.msg_lspid);
	printf("PID of msgrcv: %d \n", msq_info.msg_lrpid);
	
	return 0;
	
}
