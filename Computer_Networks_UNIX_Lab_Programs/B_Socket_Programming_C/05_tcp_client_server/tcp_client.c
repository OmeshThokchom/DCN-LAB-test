/*
 * Aim: TCP Client Program
 * Compile: gcc tcp_client.c -o tcp_client
 * Run: ./tcp_client
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

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

    write(sock_fd, "Hello from TCP client", 21);
    memset(buffer, 0, sizeof(buffer));
    read(sock_fd, buffer, sizeof(buffer) - 1);
    printf("Server: %s\n", buffer);

    close(sock_fd);
    return 0;
}

