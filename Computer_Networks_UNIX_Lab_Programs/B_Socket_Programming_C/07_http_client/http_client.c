/*
 * Aim: HTTP Client Program
 * Compile: gcc http_client.c -o http_client
 * Run: ./http_client
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(void) {
    const char *host = "example.com";
    const char *request = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";
    int sock_fd;
    struct hostent *server;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr, "Unable to resolve host\n");
        return 1;
    }

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    server_addr.sin_port = htons(80);

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock_fd);
        return 1;
    }

    write(sock_fd, request, strlen(request));
    while ((bytes_read = read(sock_fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    close(sock_fd);
    return 0;
}

