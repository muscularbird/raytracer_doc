/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** move
*/

#include "../../../include/serveur/my.h"

static bool is_dead(server_t *serv, int index, server_config_t *conf)
{
    serv->players->players[index].time_unit -= 7;
    if (check_food_death(serv, index)) {
        send(serv->client_list.clients[index].fd, "dead\n", 6, MSG_NOSIGNAL);
        remove_client(serv, index, conf);
        return true;
    }
    return false;
}

static void forward_n(server_t *serveur, int index, server_config_t *config)
{
    if (serveur->players->players[index].y - 1 < 0)
        serveur->players->players[index].y = config->height - 1;
    else
        serveur->players->players[index].y--;
}

static void forward_e(server_t *serveur, int index, server_config_t *config)
{
    if (serveur->players->players[index].x + 1 >= config->width)
        serveur->players->players[index].x = 0;
    else
        serveur->players->players[index].x++;
}

static void forward_s(server_t *serveur, int index, server_config_t *config)
{
    if (serveur->players->players[index].y + 1 >= config->height)
        serveur->players->players[index].y = 0;
    else
        serveur->players->players[index].y++;
}

static void forward_w(server_t *serveur, int index, server_config_t *config)
{
    if (serveur->players->players[index].x - 1 < 0)
        serveur->players->players[index].x = config->width - 1;
    else
        serveur->players->players[index].x--;
}

// do the move logic here
void cmd_forward(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    if (is_dead(serveur, index, config))
        return;
    switch (serveur->players->players[index].direction) {
        case 'N':
            forward_n(serveur, index, config);
            break;
        case 'E':
            forward_e(serveur, index, config);
            break;
        case 'S':
            forward_s(serveur, index, config);
            break;
        case 'W':
            forward_w(serveur, index, config);
            break;
    }
    send(serveur->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}

// do the right turn logic here
void cmd_right(server_t *serv, int index, const char *cmd,
    server_config_t *conf)
{
    int pass = 1;

    (void)cmd;
    if (is_dead(serv, index, conf))
        return;
    if (serv->players->players[index].direction == 'N') {
        serv->players->players[index].direction = 'E';
        pass = 0;
    } else if (serv->players->players[index].direction == 'E') {
        serv->players->players[index].direction = 'S';
        pass = 0;
    }
    if (serv->players->players[index].direction == 'S' && pass)
        serv->players->players[index].direction = 'W';
    else if (serv->players->players[index].direction == 'W' && pass)
        serv->players->players[index].direction = 'N';
    send(serv->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}

// do the left turn logic here
void cmd_left(server_t *serv, int index, const char *cmd,
    server_config_t *conf)
{
    int pass = 1;

    (void)cmd;
    if (is_dead(serv, index, conf))
        return;
    if (serv->players->players[index].direction == 'N') {
        serv->players->players[index].direction = 'W';
        pass = 0;
    } else if (serv->players->players[index].direction == 'E') {
        serv->players->players[index].direction = 'N';
        pass = 0;
    }
    if (serv->players->players[index].direction == 'S' && pass)
        serv->players->players[index].direction = 'E';
    else if (serv->players->players[index].direction == 'W' && pass)
        serv->players->players[index].direction = 'S';
    send(serv->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}
