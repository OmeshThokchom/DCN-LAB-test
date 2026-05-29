/*
 * Aim: TCP Client - Command Execution
 * Compile: gcc tcp_command_client.c -o tcp_command_client
 * Run: ./tcp_command_client
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8085
#define BUFFER_SIZE 1024

int main(void) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Enter command: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(sock_fd, buffer, strlen(buffer));

    printf("Command output:\n");
    while ((bytes_read = read(sock_fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    close(sock_fd);
    return 0;
}

