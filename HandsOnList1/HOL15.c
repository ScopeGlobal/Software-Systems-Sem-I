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
