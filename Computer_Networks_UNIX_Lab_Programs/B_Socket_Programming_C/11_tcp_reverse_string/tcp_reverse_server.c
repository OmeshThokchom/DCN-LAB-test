/*
 * Aim: TCP Server - Reverse String
 * Compile: gcc tcp_reverse_server.c -o tcp_reverse_server
 * Run: ./tcp_reverse_server
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8084
#define BUFFER_SIZE 1024

static void reverse(char *text) {
    int left = 0;
    int right = (int)strlen(text) - 1;

    if (right >= 0 && text[right] == '\n') {
        right--;
    }

    while (left < right) {
        char temp = text[left];
        text[left] = text[right];
        text[right] = temp;
        left++;
        right--;
    }
}

int main(void) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);
    printf("Reverse string server listening on port %d...\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    memset(buffer, 0, sizeof(buffer));
    read(client_fd, buffer, sizeof(buffer) - 1);
    reverse(buffer);
    write(client_fd, buffer, strlen(buffer));

    close(client_fd);
    close(server_fd);
    return 0;
}

