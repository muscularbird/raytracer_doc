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
