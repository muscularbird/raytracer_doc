/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** utils
*/

#include "../../include/serveur/my.h"

int find_index(serveur_t *serveur, int id_client)
{
    for (size_t i = 0; i < serveur->players->nplayers; i++) {
        if (serveur->players->players[i].fd == id_client)
            return i;
    }
    return -1;
}

int find_index_team(server_config_t *conf, const char *team_name)
{
    for (int i = 0; i < conf->team_nb; i++) {
        if (strcmp(conf->teams[i], team_name) == 0)
            return i;
    }
    return -1;
}
