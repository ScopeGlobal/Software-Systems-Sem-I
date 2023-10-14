/*
============================================================================
Name : HOL34f.c
Author : Sridhar Menon
Description :  Write a program to create a concurrent server.
 a. use fork

Date: 13th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5002
#define MAX_BUFFER_SIZE 1024

void handle_client(int client) {
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;

    bytes_received = recv(client, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Receiving data failed");
        close(client);
        return;
    }

    buffer[bytes_received] = '\0';
    printf("Received from client: %s\n", buffer);

    const char *response = "Hello from the server!";
    if (send(client, response, strlen(response), 0) == -1) {
        perror("Sending data failed");
    }

    close(client);
}

int main() {
    int server, client;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client = accept(server, (struct sockaddr *)&client_addr, &client_len);
        if (client == -1) {
            perror("Accepting connection failed");
            continue;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("Forking failed");
            close(client);
        } else if (pid == 0) {
            close(server);
            handle_client(client);
            exit(0);
        } else {
            close(client);
        }
    }

    close(server);

    return 0;
}
