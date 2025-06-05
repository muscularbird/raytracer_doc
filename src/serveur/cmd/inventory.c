/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** inventory
*/

#include "../../../include/serveur/my.h"

// do the inventory logic here
void cmd_inventory(server_t *serv, int ind, const char *cmd,
    server_config_t *conf)
{
    inventory_t *inv = &serv->players->players[ind].inventory;
    char buf[256] = {0};

    (void)cmd;
    serv->players->players[ind].time_unit -= 1;
    if (check_food_death(serv, ind)) {
        send(serv->client_list.clients[ind].fd, "dead\n", 6, MSG_NOSIGNAL);
        remove_client(serv, ind, conf);
        return;
    }
    serv->players->players[ind].next_action = time(NULL) +
    (time_t)(1.0 / (double)conf->freq);
    snprintf(buf, sizeof(buf),
    "[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, "
    "phiras %d, thystame %d]\n", inv->food, inv->linemate, inv->deraumere,
    inv->sibur, inv->mendiane, inv->phiras, inv->thystame);
    send(serv->client_list.clients[ind].fd, buf, strlen(buf), MSG_NOSIGNAL);
}
