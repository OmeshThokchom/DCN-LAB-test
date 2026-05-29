/*
 * Aim: TCP File Transfer Client
 * Compile: gcc tcp_file_transfer_client.c -o tcp_file_transfer_client
 * Run: ./tcp_file_transfer_client sample.txt
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8083
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock_fd;
    struct sockaddr_in server_addr;
    FILE *file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    if (argc < 2) {
        printf("Usage: %s <file-name>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        fclose(file);
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock_fd);
        fclose(file);
        return 1;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        write(sock_fd, buffer, bytes_read);
    }

    printf("File sent successfully\n");
    close(sock_fd);
    fclose(file);
    return 0;
}

