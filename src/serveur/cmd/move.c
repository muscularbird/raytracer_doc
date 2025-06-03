/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** move
*/

#include "../../../include/serveur/my.h"

// do the move logic here
void cmd_forward(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    send(serveur->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}

// do the right turn logic here
void cmd_right(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    send(serveur->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}

// do the left turn logic here
void cmd_left(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    send(serveur->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}
