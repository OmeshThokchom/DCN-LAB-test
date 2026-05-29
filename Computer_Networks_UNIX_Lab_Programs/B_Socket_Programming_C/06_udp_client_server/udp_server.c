/*
 * Aim: UDP Server Program
 * Compile: gcc udp_server.c -o udp_server
 * Run: ./udp_server
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main(void) {
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sock_fd);
        return 1;
    }

    printf("UDP server listening on port %d...\n", PORT);
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sock_fd, buffer, sizeof(buffer) - 1, 0,
             (struct sockaddr *)&client_addr, &client_len);
    printf("Client: %s\n", buffer);

    sendto(sock_fd, "Hello from UDP server", 21, 0,
           (struct sockaddr *)&client_addr, client_len);

    close(sock_fd);
    return 0;
}

