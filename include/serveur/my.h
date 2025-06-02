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
    #define BUFFER_SIZE 1024
    #define OK_CMD "ok\n"

typedef struct server_config_s {
    int port;
    int width;
    int height;
    char **teams;
    int team_nb;
    int *teams_count;
    int client_nb;
    int freq;
} server_config_t;

typedef struct inventory_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t;

typedef struct client_list_s {
    struct pollfd *clients;
    int count;
} client_list_t;

enum object_type {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

typedef struct object_s {
    int x;
    int y;
    enum object_type type;
    struct object_s *next;
} object_t;

typedef struct serveur_s {
    // char *map; // pour stocker la map
    int server_fd;
    struct players *players;
    object_t *object_list;
    int map_width;
    int map_height;
    client_list_t client_list;
} serveur_t;

struct player {
    struct {
        int y;
        int x;
    };
    int fd;
    unsigned short id;
    char *team_name;
    int level;
    bool isGUI;
    char buff[BUFFER_SIZE];
    inventory_t inventory;
};


struct players {
    struct player *players;
    size_t nplayers;
};


typedef void (*command_func_t)(serveur_t *, int, const char *,
    server_config_t *);

typedef struct {
    const char *name;
    command_func_t func;
} command_entry_t;

void cmd_forward(serveur_t *, int, const char *, server_config_t *);
void cmd_right(serveur_t *, int, const char *, server_config_t *);
void cmd_left(serveur_t *, int, const char *, server_config_t *);
void cmd_inventory(serveur_t *, int, const char *, server_config_t *);
void cmd_look(serveur_t *, int, const char *, server_config_t *);
void cmd_broadcast(serveur_t *, int, const char *, server_config_t *);
void cmd_connect_nbr(serveur_t *, int, const char *, server_config_t *);
void cmd_fork(serveur_t *, int, const char *, server_config_t *);
void cmd_eject(serveur_t *, int, const char *, server_config_t *);
void cmd_take(serveur_t *, int, const char *, server_config_t *);
void cmd_set(serveur_t *, int, const char *, server_config_t *);
void cmd_incantation(serveur_t *, int, const char *, server_config_t *);

static const command_entry_t command_table[] = {
    { "Forward", cmd_forward },
    { "Right", cmd_right },
    { "Left", cmd_left },
    { "Look", cmd_look },
    { "Inventory", cmd_inventory },
    { "Broadcast", cmd_broadcast },
    { "Connect_nbr", cmd_connect_nbr },
    { "Fork", cmd_fork },
    { "Eject", cmd_eject },
    { "Take", cmd_take },
    { "Set", cmd_set },
    { "Incantation", cmd_incantation },
    { NULL, NULL }
};

bool parsing(char **av, server_config_t *config);
int start_server(server_config_t *config);
int add_client(serveur_t *serv, int client_fd);
int remove_client(serveur_t *serv, int index);
int find_index(serveur_t *serveur, int id_client);
void send_log_info(serveur_t *serveur, server_config_t *config);
void recv_from_cli(serveur_t *serveur, int index, server_config_t *config);
int find_index_team(server_config_t *conf, const char *team_name);



#endif /* !MY_H_ */
