/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** take_set
*/

#include "../../../include/serveur/my.h"

// do the take logic here
void cmd_take(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    printf("Take command received from client %d\n",
        serveur->client_list.clients[index].fd);
}

// do the set logic here
void cmd_set(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    printf("Set command received from client %d\n",
        serveur->client_list.clients[index].fd);
}
