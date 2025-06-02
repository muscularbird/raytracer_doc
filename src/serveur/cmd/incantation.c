/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** incantation
*/

#include "../../../include/serveur/my.h"

// do the incantation logic here
void cmd_incantation(serveur_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    send(serveur->client_list.clients[index].fd, "Elevation underway\n",
        20, MSG_NOSIGNAL);
}
