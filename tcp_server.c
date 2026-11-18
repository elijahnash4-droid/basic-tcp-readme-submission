#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 43251
#define BUFFER_SIZE 1024

int main() {
    int server_locker, client_locker;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    socklen_t client_len = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    
    if((server_locker = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error opening locker");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_locker, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        close(server_locker);
        exit(EXIT_FAILURE);
    }

    if (listen(server_locker, 3) < 0) {
        perror("listen failed");
        close(server_locker);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    if ((client_locker = accept(server_locker, (struct sockaddr *)&address, (socklen_t*)&addrlen))< 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    ssize_t bytes_received = recv(client_locker, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("Error receiving data");
    }
    else {
        printf("Message sent: %s\n", buffer);
    }

    const char *response = "Hello, Client!";
    if(send(client_locker, response, strlen(response), 0) < 0) {
        perror("Send error");
        exit(EXIT_FAILURE);
    }

    close(client_locker);
    close(server_locker);
}