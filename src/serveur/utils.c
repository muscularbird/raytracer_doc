/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** utils
*/

#include "../../include/serveur/my.h"

int find_index(server_t *serveur, int id_client)
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

char *extract_command(char *buffer)
{
    char *end = strstr(buffer, "\n");
    size_t cmd_len = 0;
    char *cmd = NULL;

    if (!end)
        return NULL;
    cmd_len = end - buffer;
    cmd = malloc(cmd_len + 1);
    if (!cmd)
        return NULL;
    strncpy(cmd, buffer, cmd_len);
    cmd[cmd_len] = '\0';
    return cmd;
}

void shift_buffer(char *buffer)
{
    char *end = strstr(buffer, "\n");

    if (!end)
        return;
    end += 1;
    memmove(buffer, end, strlen(end) + 1);
}
