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

bool check_food_death(server_t *serveur, int i)
{
    struct player *player = &serveur->players->players[i];

    if (player->time_unit <= 0 && player->inventory.food > 0) {
        player->inventory.food -= 1;
        player->time_unit += 126;
        printf("Player %d from team %s has lost 1 food unit."
            "Remaining food: %d\n",
            player->fd, player->team_name, player->inventory.food);
        return false;
    }
    if (player->inventory.food == 0 && player->time_unit <= 0) {
        printf("Player %d from team %s has died due to starvation.\n",
            player->fd, player->team_name);
        return true;
    }
    return false;
}
