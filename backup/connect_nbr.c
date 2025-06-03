/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** connect_nbr
*/

#include "../../../include/serveur/my.h"

// do the connect number logic here
void cmd_connect_nbr(serveur_t *serv, int index, const char *cmd,
    server_config_t *conf)
{
    char buffer[13] = {0};
    int pos = find_index_team(conf, serv->players->players[index].team_name);
    int result = conf->teams_count_max[pos] - conf->teams_count_connect[pos];

    (void)cmd;
    snprintf(buffer, sizeof(buffer), "%d\n", result);
    send(serv->client_list.clients[index].fd, buffer,
        strlen(buffer), MSG_NOSIGNAL);
}
