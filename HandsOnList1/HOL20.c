/*
============================================================================
Name : HOL20.c
Author : Sridhar Menon
Description :  Find out the priority of your running program. Modify the priority with nice command.
Date: 25th Aug, 2023.
============================================================================
*/

#include<sys/time.h>
#include<sys/resource.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void) {

	int pid = getpid();
	int priority = getpriority(PRIO_PROCESS, pid);
	
	printf("The Priority of our Process is - %d \n", priority);
	
	getchar();
	
	int new_priority;
	printf("Enter new priority- ");
	scanf("%d", &new_priority);
	
	int set_status = setpriority(PRIO_PROCESS, pid, new_priority);
	
	if (set_status < 0) {
		perror("Set Priority Failed ");
		return -1;
	}
	printf("New Priority: %d \n", getpriority(PRIO_PROCESS, pid));
	getchar();
	return 0;

}
