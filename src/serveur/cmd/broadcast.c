/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** broadcast
*/

#include "../../../include/serveur/my.h"

// do the broadcast logic here
void cmd_broadcast(serveur_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    printf("Broadcast command received from client %d\n",
        serveur->client_list.clients[index].fd);
}
