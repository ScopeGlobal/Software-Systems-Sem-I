/*
============================================================================
Name : HOL33c.c
Author : Sridhar Menon
Description :   Write a program to communicate between two machines using socket.

Date: 13th Oct, 2023.
============================================================================
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(void) {

	int client;
	struct sockaddr_in server_addr;
	char buf[1024];
	
	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0) {
		perror("Server side Socket creation failed");
		return -1;
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5002);
	inet_pton(AF_INET, "172.24.120.60", &(server_addr.sin_addr));
	
	int connect_stat = connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (connect_stat < 0) {
		perror("Connection Failed");
		return -1;
	}
	
	char sendbuf[1024];
	printf("Enter the message to be sent to Client- ");
	scanf("%[^\n]", sendbuf);
	
	int send_stat = send(client, sendbuf, sizeof(sendbuf), 0);
	if (send_stat < 0) {
		perror("Sending Failed");
		return -1;
	}
	
	
	int bytes = recv(client, buf, sizeof(buf), 0);
	if (bytes < 0) {
		perror("Receiving Failed");
		return -1;
	}
	
	buf[bytes] = '\0';
	printf("Message received from Client: %s", buf);
	
	close(client);
	
	return 0;
	
}
