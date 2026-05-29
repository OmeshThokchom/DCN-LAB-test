/*
 * Aim: TCP Forking Multi-Client Server
 * Compile: gcc tcp_forking_server.c -o tcp_forking_server
 * Run: ./tcp_forking_server
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define PORT 8087
#define BUFFER_SIZE 1024

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
    printf("Forking server listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            continue;
        }

        if (fork() == 0) {
            close(server_fd);
            memset(buffer, 0, sizeof(buffer));
            read(client_fd, buffer, sizeof(buffer) - 1);
            printf("Client says: %s\n", buffer);
            write(client_fd, "Handled by child process", 24);
            close(client_fd);
            return 0;
        }

        close(client_fd);
        while (waitpid(-1, NULL, WNOHANG) > 0) {
        }
    }

    close(server_fd);
    return 0;
}

