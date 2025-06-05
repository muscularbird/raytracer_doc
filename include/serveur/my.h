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
    #include <time.h>
    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.05
    #define PHIRAS_DENSITY 0.05
    #define THYSTAME_DENSITY 0.01

    #define EXIT_FAIL 84
    #define EXIT_SUCCESS 0
    #define BUFFER_SIZE 1024
    #define OK_CMD "ok\n"
    #define KO_CMD "ko\n"

typedef struct server_config_s {
    int port;
    int width;
    int height;
    char **teams;
    int team_nb;
    int *teams_count_max;
    int *teams_count_connect;
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

enum obj_type {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    LAST_OBJECT
};

typedef struct tile_s {
    int x;
    int y;
    enum obj_type* obj;
} tile_t;

typedef struct server_s {
    int server_fd;
    struct players *players;
    tile_t **map;
    float *map_density;
    int map_width;
    int map_height;
    client_list_t client_list;
} server_t;

struct player {
    struct {
        int y;
        int x;
        char direction;
    };
    int fd;
    bool is_loged;
    unsigned short id;
    char *team_name;
    int nb_bad_cmd;
    int req_without_answer;
    int level;
    int time_unit;
    time_t next_action;
    bool isGUI;
    char buff[BUFFER_SIZE];
    inventory_t inventory;
};


struct players {
    struct player *players;
    size_t nplayers;
};


typedef void (*command_func_t)(server_t *, int, const char *,
    server_config_t *);

typedef struct {
    const char *name;
    command_func_t func;
} command_entry_t;

void cmd_forward(server_t *, int, const char *, server_config_t *);
void cmd_right(server_t *, int, const char *, server_config_t *);
void cmd_left(server_t *, int, const char *, server_config_t *);
void cmd_inventory(server_t *, int, const char *, server_config_t *);
void cmd_look(server_t *, int, const char *, server_config_t *);
void cmd_broadcast(server_t *, int, const char *, server_config_t *);
void cmd_connect_nbr(server_t *, int, const char *, server_config_t *);
void cmd_fork(server_t *, int, const char *, server_config_t *);
void cmd_eject(server_t *, int, const char *, server_config_t *);
void cmd_take(server_t *, int, const char *, server_config_t *);
void cmd_set(server_t *, int, const char *, server_config_t *);
void cmd_incantation(server_t *, int, const char *, server_config_t *);

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
int add_client(server_t *serv, int client_fd);
int remove_client(server_t *serv, int index, server_config_t *config);
int find_index(server_t *serveur, int id_client);
void send_log_info(server_t *serveur);
void recv_from_cli(server_t *serveur, int index, server_config_t *config);
int find_index_team(server_config_t *conf, const char *team_name);
char *extract_command(char *buffer);
void shift_buffer(char *buffer);
int validate_log_info(const char *buf, server_t *serv,
    server_config_t *conf, int index);
bool check_food_death(server_t *serveur, int i);
void see_cmd(server_t *serveur, int index, server_config_t *config);
// map handling
int generate_map(server_t *serv);


#endif /* !MY_H_ */
