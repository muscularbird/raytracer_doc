#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    printf("Client socket fd: %d\n", sock);

    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    char buf[BUF_SIZE];
    ssize_t n;
    while ((n = read(sock, buf, BUF_SIZE - 1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
        break;
    }

    // Send a message to the server
    const char *msg = "Epitech\n";
    ssize_t sent = send(sock, msg, strlen(msg), 0);
    if (sent < 0) {
        perror("send");
    } else {
        printf("Sent %zd bytes to server\n", sent);
    }

    close(sock);
    return 0;
}