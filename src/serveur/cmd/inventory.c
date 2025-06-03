/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** inventory
*/

#include "../../../include/serveur/my.h"

// do the inventory logic here
void cmd_inventory(server_t *serveur, int index, const char *cmd,
    server_config_t *config)
{
    (void)cmd;
    (void)config;
    printf("Inventory command received from client %d\n",
        serveur->client_list.clients[index].fd);
}
