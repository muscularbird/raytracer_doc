/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <poll.h>
    #include <signal.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <arpa/inet.h>
    #include <limits.h>

    #define EXIT_FAIL 84
    #define EXIT_SUCCESS 0

typedef struct server_config_s {
    int port;
    int width;
    int height;
    char **teams;
    int client_nb;
    int freq;
} server_config_t;

typedef struct inventory_s {
    int food;
    int sibur;
    int phiras;
} inventory_t;

typedef struct client_list_s {
    struct pollfd *clients;
    int count;
} client_list_t;

typedef struct serveur_s {
    // char *map; // pour stocker la map
    int server_fd;
    struct players *players; // pour stocker les info des ia
    client_list_t client_list;
} serveur_t;

struct player {
    struct {
        int y;
        int x;
    };
    int fd;
    unsigned short id;
    int level;
    bool isGUI;
    inventory_t inventory;
};

struct players {
    struct player *players;
    size_t nplayers;
};

bool parsing(char **av, server_config_t *config);
int start_server(server_config_t *config);

#endif /* !MY_H_ */
