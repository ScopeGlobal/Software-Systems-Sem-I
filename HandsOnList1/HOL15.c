/*
============================================================================
Name : HOL15.c
Author : Sridhar Menon
Description : Write a program to display the environmental variable of the user (use environ).
Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

extern char **environ;

int main(void) {

	int i = 0;
	char **env = environ;
	
	printf("The environment variables: \n");
	
	while(env[i]) {
		printf("%s\n", env[i]);
		i++;
	}
	return 0;
}
