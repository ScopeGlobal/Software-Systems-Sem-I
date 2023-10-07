#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<sys/msg.h>

int main(void) {

	key_t key = ftok(".", 24);
	if (key < 0) {
		perror("Key creation failed");
		return -1;
	}
	
	int msgq = msgget(key, 0666);
	if (msgq < 0) {
		perror("Message Queue creation failed");
		return -1;
	}
	
	struct msqid_ds msq_info;
	
	int msgq_stat = msgctl(msgq, IPC_STAT, &msq_info);
	if (msgq_stat < 0) {
		perror("Stat retrieval failed");
		return -1;
	}
	
	printf("Permissions before change: 0%o \n", msq_info.msg_perm.mode);
	
	msq_info.msg_perm.mode = 0644;
	int msgq_set = msgctl(msgq, IPC_SET, &msq_info);
	if (msgq_set < 0) {
		perror("Permission setting failed");
		return -1;
	}
	
	printf("Permissions after change 0%o \n", msq_info.msg_perm.mode);
	
	return 0;

}
