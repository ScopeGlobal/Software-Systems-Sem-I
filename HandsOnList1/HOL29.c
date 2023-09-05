#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sched.h>

int main(void) {

	int pid = getpid();
	
	int scheduler;
	
	scheduler = sched_getscheduler(pid);
	
	printf("%d \n", scheduler);
	
	switch(scheduler) {
	
		case SCHED_FIFO: printf("SCHED_FIFO \n"); break;
		case SCHED_RR: printf("SCHED_RR \n"); break;
		case 0: printf("SCHED_NORMAL \n"); break;
		case 3: printf("SCHED_BATCH \n"); break;
		case 5: printf("SCHED_IDLE \n"); break;
		case 6: printf("SCHED_DEADLINE"); break;
		default: printf("Invalid \n"); break;
		
	}
	
	printf("What would you like to change the priority to? \n");
	printf("1. SCHED_FIFO \n");
	printf("2. SCHED_RR \n");
	printf("Enter your choice- ");
	int choice;
	
	scanf("%d", &choice);
	struct sched_param sp;
	sp.sched_priority = 50;
	int ret;
	printf("Your choice is %d \n", choice);
	if (choice == 1) {
		ret = sched_setscheduler(pid, 1, &sp);
		if (ret < 0) {
			perror("Set Scheduler ");
			return -1;
		}
		printf("Changed to SCHED_FIFO \n");
	} else {
		ret = sched_setscheduler(pid, 2, &sp);
		if (ret < 0) {
			perror("Set Scheduler ");
			return -1;
		}
		printf("Changed to SCHED_RR \n");
	}
	
	return 0;
} 
