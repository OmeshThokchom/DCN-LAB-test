/*
 * Aim: UDP Time Server
 * Compile: gcc udp_time_server.c -o udp_time_server
 * Run: ./udp_time_server
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define PORT 8086

int main(void) {
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char request[32];
    time_t current_time;
    char *time_text;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("UDP time server listening on port %d...\n", PORT);

    recvfrom(sock_fd, request, sizeof(request), 0,
             (struct sockaddr *)&client_addr, &client_len);
    current_time = time(NULL);
    time_text = ctime(&current_time);
    sendto(sock_fd, time_text, strlen(time_text), 0,
           (struct sockaddr *)&client_addr, client_len);

    close(sock_fd);
    return 0;
}

