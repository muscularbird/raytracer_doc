/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** connect_nbr
*/

#include "../../../include/serveur/my.h"

// do the connect number logic here
void cmd_connect_nbr(serveur_t *serv, int index, const char *cmd,
    server_config_t *config)
{
    char buffer[13] = {0};
    int pos = find_index_team(config, serv->players->players[index].team_name);
    int result = serv->client_list.count - config->teams_count[pos];

    (void)cmd;
    buffer[12] = '\n';
    snprintf(buffer, sizeof(buffer), "%d", result);
    send(serv->client_list.clients[index].fd, buffer,
        strlen(buffer), MSG_NOSIGNAL);
}
