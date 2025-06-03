/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** fork
*/

#include "../../../include/serveur/my.h"

// do the fork logic here
void cmd_fork(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    printf("Fork command received from client %d\n",
        serveur->client_list.clients[index].fd);
    send(serveur->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}
