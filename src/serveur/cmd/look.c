/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** look
*/

#include "../../../include/serveur/my.h"

// do the look logic here
void cmd_look(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    printf("Look command received from client %d\n",
        serveur->client_list.clients[index].fd);
}
