#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(void) {

	int server, client;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	char buf[1024];
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server < 0) {
		perror("Server side Socket creation failed");
		return -1;
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5002);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	int bind_stat = bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (bind_stat < 0) {
		perror("Binding Failed");
		return -1;
	}
	
	int listen_stat = listen(server, 5);
	if (listen_stat < 0) {
		perror("Listen Failed");
		return -1;
	}
	
	printf("The server is now listening on port 5002 \n");
	
	client = accept(server, (struct sockaddr *)&client_addr, &client_len);
	if (client < 0) {
		perror("Client Acceptance Failed");
		return -1;
	}
	
	int bytes = recv(client, buf, sizeof(buf), 0);
	if (bytes < 0) {
		perror("Receiving Failed");
		return -1;
	}
	
	buf[bytes] = '\0';
	printf("Message received from Client: %s", buf);
	
	char sendbuf[1024];
	printf("Enter the message to be sent to Client- ");
	scanf("%[^\n]", sendbuf);
	
	int send_stat = send(client, sendbuf, sizeof(sendbuf), 0);
	if (send_stat < 0) {
		perror("Sending Failed");
		return -1;
	}
	
	close(server);
	close(client);
	
	return 0;
	
}
