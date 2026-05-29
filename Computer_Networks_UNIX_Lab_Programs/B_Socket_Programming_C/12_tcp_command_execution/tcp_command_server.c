/*
 * Aim: TCP Server - Command Execution
 * Compile: gcc tcp_command_server.c -o tcp_command_server
 * Run: ./tcp_command_server
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8085
#define BUFFER_SIZE 1024

int main(void) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char command[BUFFER_SIZE], output[BUFFER_SIZE];
    FILE *pipe;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);
    printf("Command server listening on port %d...\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    memset(command, 0, sizeof(command));
    read(client_fd, command, sizeof(command) - 1);

    pipe = popen(command, "r");
    if (pipe == NULL) {
        write(client_fd, "Command execution failed\n", 25);
    } else {
        while (fgets(output, sizeof(output), pipe) != NULL) {
            write(client_fd, output, strlen(output));
        }
        pclose(pipe);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

