/*
 * Aim: DNS Lookup and IP Address Validation
 * Compile: gcc dns_lookup_ip_validation.c -o dns_lookup_ip_validation
 * Run: ./dns_lookup_ip_validation example.com 8.8.8.8
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct hostent *host;
    struct in_addr addr;

    if (argc < 3) {
        printf("Usage: %s <hostname> <ip-address>\n", argv[0]);
        return 1;
    }

    host = gethostbyname(argv[1]);
    if (host == NULL) {
        printf("DNS lookup failed for %s\n", argv[1]);
    } else {
        printf("Official name: %s\n", host->h_name);
        printf("IP address: %s\n", inet_ntoa(*(struct in_addr *)host->h_addr));
    }

    if (inet_pton(AF_INET, argv[2], &addr) == 1) {
        printf("%s is a valid IPv4 address\n", argv[2]);
    } else {
        printf("%s is not a valid IPv4 address\n", argv[2]);
    }

    return 0;
}

