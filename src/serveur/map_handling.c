/*
** EPITECH PROJECT, 2025
** zappy_mirroring
** File description:
** map_handling
*/

#include "../../include/serveur/my.h"

int generate_map(server_t *serv)
{
    int i = 0;
    int j = 0;

    serv->map_density = (float[]){0.5, 0.3, 0.15, 0.1, 0.05, 0.05, 0.01};
    serv->map = malloc(sizeof(tile_t) * serv->map_width * serv->map_height);
    if (!serv->map) {
        perror("Memory allocation failed for map");
        return EXIT_FAIL;
    }
    for (i = 0; i < serv->map_height; i++) {
        for (j = 0; j < serv->map_width; j++) {
            serv->map[i * serv->map_width + j].x = j;
            serv->map[i * serv->map_width + j].y = i;
            serv->map[i * serv->map_width + j].objects = NULL;
        }
    }
    return EXIT_SUCCESS;
}

void dispatch_objects(server_t *serv)
{
    int rand_W = 0;
    int rand_H = 0;
    int obj_nbr = 0;
    tile_t *tile = NULL;

    srand(time(NULL));
    for (int i = 0; i < serv->map_height * serv->map_width; i++) {
        rand_W = rand() % serv->map_width;
        rand_H = rand() % serv->map_height;
    }
    for (enum obj_type i = 0; i < LAST_OBJECT; i++) {
        obj_nbr = (serv->map_density[i] * serv->map_width * serv->map_height);
        for (int j = 0; j < obj_nbr; j++) {
            rand_W = rand() % serv->map_width;
            rand_H = rand() % serv->map_height;
            tile = &serv->map[rand_H * serv->map_width + rand_W];
            tile->obj = realloc(tile->obj, sizeof(enum obj_type) * (j + 1));
            tile->obj[j] = i;
        }
    }
}
