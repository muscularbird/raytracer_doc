/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** add_del_user
*/

#include "../../include/serveur/my.h"

// ------------------- REMOVE CLIENT -------------------
static void free_player(players_t *player, int ind, server_config_t *conf)
{
    int pos_team = 0;

    if (player->players[ind].team_name) {
        find_index_team(conf, player->players[ind].team_name);
        conf->teams_count_connect[pos_team]--;
        free(player->players[ind].team_name);
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
    players_t *players = serv->players;
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
            sizeof(player_t));
        if (!players->players)
            return 0 * fprintf(stderr, "Erreur realloc players\n");
    } else {
        free(players->players);
        players->players = NULL;
    }
    return do_proper_logout(fd, index, &serv->client_list);
}

// ------------------- ADD CLIENT -------------------
static void init_player(player_t *__players, int index, int id, int fd)
{
    __players[index] = (player_t) {
        .x = -1,
        .y = -1,
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

void init_pos_player(player_t *players, int ind,
    server_config_t *conf)
{
    char directions[] = {'N', 'S', 'E', 'W'};
    int chosen_direction = rand() % 4;

    players[ind].x = rand() % conf->width;
    players[ind].y = rand() % conf->height;
    players[ind].direction = directions[chosen_direction];
}

static bool create_player(players_t *players, int fd,
    server_config_t *conf)
{
    static unsigned short id = 1;
    player_t *__players;

    (void)conf;
    __players = realloc(players->players,
        sizeof(player_t) * (players->nplayers + 1));
    if (__players == NULL)
        return false;
    players->players = __players;
    init_player(players->players, players->nplayers, id, fd);
    players->nplayers++;
    id++;
    return true;
}

void print_player(const player_t *p, server_t *serv)
{
    char *buff = calloc(BUFFER_SIZE + 1, sizeof(char));
    const char *team_name_safe = (p->team_name && strlen(p->team_name) <= 100)
    ? p->team_name : "TOO_LONG_OR_NULL";
    char buff_safe[101] = {0};

    if (!buff)
        return;
    strncpy(buff_safe, (strlen(p->buff) <= 100) ? p->buff : "TOO_LONG", 100);
    snprintf(buff, BUFFER_SIZE,
        "Player {\n  id: %d\n  fd: %d\n  x: %d\n  y: %d\n"
        "  direction: %c\n  team_name: %s\n  is_loged: %s\n"
        "  next_action: %ld\n  buff: \"%s\"\n}\n",
        p->id, p->fd, p->x, p->y, p->direction, team_name_safe,
        p->is_loged ? "true" : "false", (long)p->next_action, buff_safe
    );
    write_log(serv->log_file, buff, 0);
    free(buff);
}

int add_client(server_t *serv, int client_fd, server_config_t *config)
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
    create_player(serv->players, client_fd, config);
    if (config->debug)
        print_player(&serv->players->players[serv->players->nplayers - 1],
            serv);
    printf("230 -> User %d connected\n", client_fd);
    return 0;
}
