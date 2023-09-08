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
	printf("Enter new Nice value- ");
	scanf("%d", &new_priority);
	
	nice(new_priority);
	printf("New Nice value: %d \n", nice(0));
	getchar();
	return 0;

}
