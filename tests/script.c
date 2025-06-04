#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER "127.0.0.1"  // Adresse du serveur FTP
#define PORT 4242            // Port FTP standard
#define BUFFER_SIZE 1024

void read_response(int sock) {
    char buffer[BUFFER_SIZE];
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Réponse du serveur:\n %s", buffer);
    }
}

void send_command(int sock, const char *cmd, int read) {
    send(sock, cmd, strlen(cmd), 0);
    if (read)
        read_response(sock);
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Erreur de création du socket");
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connexion au serveur échouée");
        close(sock);
        return EXIT_FAILURE;
    }


    read_response(sock);
    send_command(sock, "Epitech\n", 0);
    sleep(0.5);
    read_response(sock);
    sleep(1);
    send_command(sock, "Connect_nbr\nFork\n", 1);
    sleep(2);
    printf("finish\n");

}


