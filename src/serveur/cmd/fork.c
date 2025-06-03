/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** fork
*/

#include "../../../include/serveur/my.h"

// do the fork logic here
void cmd_fork(server_t *serv, int index, const char *cmd,
    server_config_t *conf)
{
    int pos = find_index_team(conf, serv->players->players[index].team_name);

    (void)cmd;
    conf->teams_count_max[pos]++;
    send(serv->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}
