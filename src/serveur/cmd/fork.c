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
    serv->players->players[index].time_unit -= 42;
    if (check_food_death(serv, index)) {
        send(serv->client_list.clients[index].fd, "dead\n", 6, MSG_NOSIGNAL);
        remove_client(serv, index);
        return;
    }
    conf->teams_count_max[pos]++;
    send(serv->client_list.clients[index].fd, OK_CMD, 3, MSG_NOSIGNAL);
}
