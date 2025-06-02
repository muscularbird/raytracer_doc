/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** eject
*/

#include "../../../include/serveur/my.h"

// do the eject logic here
void cmd_eject(serveur_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    printf("Eject command received from client %d\n",
        serveur->client_list.clients[index].fd);
}
