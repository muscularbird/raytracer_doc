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

static void dispatch(server_t *serveur, int i, server_config_t *config)
{
    client_list_t *cli_list = &serveur->client_list;

    if (cli_list->clients[i].revents & POLLIN) {
        if (cli_list->clients[i].fd == serveur->server_fd)
            send_log_info(serveur, config);
        else
            recv_from_cli(serveur, i, config);
    }
}

static void server_shutdown(client_list_t *cli_list, server_t *serveur)
{
    printf("\n\n---------- Server shutting down... ----------\n");
    for (int i = 0; i < cli_list->count; i++) {
        close(cli_list->clients[i].fd);
        free(serveur->players->players[i].team_name);
    }
    free(serveur->players->players);
    free(serveur->players);
    free(cli_list->clients);
}

static int run_serv(server_t *serveur, server_config_t *config)
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
            dispatch(serveur, i, config);
    }
    server_shutdown(cli_list, serveur);
    return 0;
}

int start_server(server_config_t *config)
{
    server_t server = {0};

    server.server_fd = init_server(config->port);
    if (server.server_fd < 0)
        return 1;
    run_serv(&server, config);
    return 0;
}
