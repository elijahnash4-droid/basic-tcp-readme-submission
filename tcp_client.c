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
    int client_locker;
    struct sockaddr_in serv_addr;
    char message[BUFFER_SIZE] = {0};
    char buffer[BUFFER_SIZE] = {0};

    
    if ((client_locker = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error opening locker");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_locker, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection to server failed");
        close(client_locker);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");

    printf("Enter message: ");
    fgets(message, BUFFER_SIZE, stdin);

    message[strcspn(message, "\n")] = 0;

    if (send(client_locker, message, strlen(message), 0) < 0) {
        perror("Send error"); // Print error message if sending data fails
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_received = recv(client_locker, buffer, sizeof(buffer), 0);

    if (bytes_received < 0){
        perror("Error receiving data");
    }
    else {
        printf("Response from server: %s\n", buffer);
    }

    close(client_locker);

    return 0;
}