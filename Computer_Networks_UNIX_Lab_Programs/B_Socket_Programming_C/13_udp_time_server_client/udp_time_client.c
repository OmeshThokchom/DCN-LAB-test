/*
 * Aim: UDP Time Client
 * Compile: gcc udp_time_client.c -o udp_time_client
 * Run: ./udp_time_client
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8086
#define BUFFER_SIZE 1024

int main(void) {
    int sock_fd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    sendto(sock_fd, "time", 4, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sock_fd, buffer, sizeof(buffer) - 1, 0,
             (struct sockaddr *)&server_addr, &server_len);

    printf("Server time: %s", buffer);
    close(sock_fd);
    return 0;
}

