/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** add_del_user
*/

#include "../../include/serveur/my.h"

// ------------------- REMOVE CLIENT -------------------
static void free_player(struct players *player, int ind, server_config_t *conf)
{
    int pos_team = 0;

    if (player->player[ind].team_name) {
        find_index_team(conf, player->player[ind].team_name);
        conf->teams_count_connect[pos_team]--;
        free(player->player[ind].team_name);
    }
}

static int do_proper_logout(int fd, int index, client_list_t *cli_list)
{
    printf("226 -> User %d deconnected\n", fd);
    close(fd);
    for (int i = index; i < cli_list->count - 1; i++)
        cli_list->clients[i] = cli_list->clients[i + 1];
    cli_list->count--;
    if (cli_list->count > 0) {
        cli_list->clients = realloc(cli_list->clients, cli_list->count *
            sizeof(struct pollfd));
        if (!cli_list->clients)
            return 0 * fprintf(stderr, "Erreur realloc clients\n");
    } else {
        free(cli_list->clients);
        cli_list->clients = NULL;
    }
    return 1;
}

int remove_client(server_t *serv, int index, server_config_t *config)
{
    struct players *players = serv->players;
    int fd = serv->client_list.clients[index].fd;
    int player_index = find_index(serv, fd);

    if (player_index == -1)
        return do_proper_logout(fd, index, &serv->client_list);
    free_player(players, player_index, config);
    for (size_t j = player_index; j < players->nplayers - 1; j++)
        players->players[j] = players->players[j + 1];
    players->nplayers--;
    if (players->nplayers > 0) {
        players->players = realloc(players->players, players->nplayers *
            sizeof(struct player));
        if (!players->players)
            return 0 * fprintf(stderr, "Erreur realloc players\n");
    } else {
        free(players->players);
        players->players = NULL;
    }
    return do_proper_logout(fd, index, &serv->client_list);
}

// ------------------- ADD CLIENT -------------------
static void init_player(struct player *__players, int index, int id, int fd)
{
    __players[index] = (struct player) {
        .x = 0,
        .y = 0,
        .direction = 'N',
        .id = id,
        .fd = fd,
        .buff = {0},
        .team_name = NULL,
        .is_loged = false,
        .inventory.food = 10,
        .next_action = time(NULL)
    };
}

static bool create_player(struct players *players, int fd)
{
    static unsigned short id = 1;
    struct player *__players;

    __players = realloc(players->players,
        sizeof(struct player) * (players->nplayers + 1));
    if (__players == NULL)
        return false;
    players->players = __players;
    init_player(players->players, players->nplayers, id, fd);
    players->nplayers++;
    id++;
    return true;
}

int add_client(server_t *serv, int client_fd)
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
    printf("230 -> User %d connected\n", client_fd);
    return 0;
}
