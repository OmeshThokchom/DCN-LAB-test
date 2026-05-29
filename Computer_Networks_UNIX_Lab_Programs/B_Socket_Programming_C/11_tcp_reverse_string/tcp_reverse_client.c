/*
 * Aim: TCP Client - Reverse String
 * Compile: gcc tcp_reverse_client.c -o tcp_reverse_client
 * Run: ./tcp_reverse_client
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8084
#define BUFFER_SIZE 1024

int main(void) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Enter string: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(sock_fd, buffer, strlen(buffer));

    memset(buffer, 0, sizeof(buffer));
    read(sock_fd, buffer, sizeof(buffer) - 1);
    printf("Reversed string: %s\n", buffer);

    close(sock_fd);
    return 0;
}

