/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** serv
*/

#include "../../include/serveur/my.h"

static int init_server(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {.sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY, .sin_port = htons(port)};

    if (server_fd == -1)
        return -1 + 0 * fprintf(stderr, "Error socket\n");
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    if (bind(server_fd, (void *)&server_addr, sizeof(server_addr)) < 0) {
        close(server_fd);
        return -1 + 0 * fprintf(stderr, "Error bind\n");
    }
    if (listen(server_fd, 5) < 0) {
        close(server_fd);
        return -1 + 0 * fprintf(stderr, "Error listen\n");
    }
    printf("Listening on port %d\nWaiting for connection...\n", port);
    return server_fd;
}

static int *get_ptr_serv(void)
{
    static int run_serv = 1;

    return &run_serv;
}

static void sighandler(int sig)
{
    int *run_serv = get_ptr_serv();

    if (sig == SIGINT)
        *run_serv = 0;
}

bool create_player(struct players *players, int fd)
{
    static unsigned short id = 1;
    struct player *__players;

    __players = realloc(players->players,
        sizeof(struct player) * (players->nplayers + 1));
    if (__players == NULL) {
        return false;
    }
    __players[players->nplayers] = (struct player) {
        .x = 0,
        .y = 0,
        .id = id,
        .fd = fd
    };
    players->players = __players;
    players->nplayers++;
    id++;
    return true;
}

int add_client(serveur_t *serv, int client_fd)
{
    client_list_t *cli_list = &serv->client_list;

    cli_list->clients = realloc(cli_list->clients, (cli_list->count + 1)
        * sizeof(struct pollfd));
    if (!cli_list->clients)
        return 1 + 0 * fprintf(stderr, "Erreur realloc\n");
    cli_list->clients[cli_list->count].fd = client_fd;
    cli_list->clients[cli_list->count].events = POLLIN;
    cli_list->clients[cli_list->count].revents = 0;
    cli_list->count++;
    create_player(serv->players, client_fd);
    return 0;
}

static int find_index(serveur_t *serveur, int id_client)
{
    for (size_t i = 0; i < serveur->players->nplayers; i++) {
        if (serveur->players->players[i].fd == id_client)
            return i;
    }
    return -1;
}

void send_map(serveur_t *serveur)
{
    int client_fd = accept(serveur->server_fd, NULL, NULL);
    int index = find_index(serveur, client_fd - 1);

    if (client_fd < 0) {
        fprintf(stderr, "Error accept");
        return;
    }
    if (index == -1) {
        close(client_fd);
        return;
    }
    add_client(serveur, client_fd);
    printf("230 -> User %d connected\n", client_fd);
    send(client_fd, "WELCOME\n", 9, MSG_NOSIGNAL);
}

// else
//     recv_from_cli(serveur, i);
static void dispatch(serveur_t *serveur, int i)
{
    client_list_t *cli_list = &serveur->client_list;

    if (cli_list->clients[i].revents & POLLIN) {
        if (cli_list->clients[i].fd == serveur->server_fd)
            send_map(serveur);
    }
}

static int run_serv(serveur_t *serveur)
{
    client_list_t *cli_list = &serveur->client_list;

    serveur->players = calloc(sizeof(struct players), 1);
    add_client(serveur, serveur->server_fd);
    signal(SIGINT, sighandler);
    while (*get_ptr_serv()) {
        if (poll(cli_list->clients, cli_list->count, -1) < 0
            && errno != EINTR) {
            free(cli_list->clients);
            return 1 + 0 * fprintf(stderr, "Error poll\n");
        }
        for (int i = 0; i < cli_list->count; i++)
            dispatch(serveur, i);
    }
    free(cli_list->clients);
    return 0;
}

int start_server(server_config_t *config)
{
    serveur_t server = {0};

    server.server_fd = init_server(config->port);
    if (server.server_fd < 0)
        return 1;
    run_serv(&server);
    return 0;
}
