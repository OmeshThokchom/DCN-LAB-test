/*
 * Aim: TCP Chat Client
 * Compile: gcc tcp_chat_client.c -o tcp_chat_client
 * Run: ./tcp_chat_client
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8082
#define BUFFER_SIZE 1024

int main(void) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE], response[BUFFER_SIZE];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock_fd);
        return 1;
    }

    while (1) {
        printf("You: ");
        fgets(message, sizeof(message), stdin);
        write(sock_fd, message, strlen(message));

        if (strncmp(message, "exit", 4) == 0) {
            break;
        }

        memset(response, 0, sizeof(response));
        read(sock_fd, response, sizeof(response) - 1);
        printf("Server: %s", response);
    }

    close(sock_fd);
    return 0;
}

