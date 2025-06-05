/*
** EPITECH PROJECT, 2025
** zappy_mirroring
** File description:
** map_handling
*/

#include "../../include/serveur/my.h"

int second_for(enum obj_type i, server_t *serv, int object_count)
{
    int rand_width;
    int rand_height;
    tile_t *tile;

    for (int j = 0; j < object_count; j++) {
        rand_width = rand() % serv->map_width;
        rand_height = rand() % serv->map_height;
        tile = &serv->map[rand_height][rand_width];
        tile->obj = realloc(tile->obj, sizeof(enum obj_type) * (j + 1));
        if (!tile->obj) {
            perror("Memory allocation failed for tile objects");
            return EXIT_FAIL;
        }
        tile->obj[j] = i;
    }
    return EXIT_SUCCESS;
}

int dispatch_objects(server_t *serv)
{
    int object_count;

    srand(time(NULL));
    for (enum obj_type i = 0; i < LAST_OBJECT; i++) {
        object_count = (serv->map_density[i] * serv->map_width *
            serv->map_height);
        second_for(i, serv, object_count);
    }
    return 0;
}

int generate_map(server_t *serv)
{
    serv->map_density = (float[]){0.5, 0.3, 0.15, 0.1, 0.05, 0.05, 0.01};
    serv->map = malloc(sizeof(tile_t *) * serv->map_height);
    for (int i = 0; i < serv->map_height; i++) {
        serv->map[i] = malloc(sizeof(tile_t) * serv->map_width);
        if (!serv->map[i]) {
            perror("Memory allocation failed for map row");
            return EXIT_FAIL;
        }
    }
    if (!serv->map) {
        perror("Memory allocation failed for map");
        return EXIT_FAIL;
    }
    for (int i = 0; i < serv->map_height; i++) {
        for (int j = 0; j < serv->map_width; j++) {
            serv->map[i * serv->map_height][j].x = j;
            serv->map[i * serv->map_height][j].y = i;
            serv->map[i * serv->map_height][j].obj = malloc(sizeof(enum obj_type) *1);
        }
    }
    dispatch_objects(serv);
    return EXIT_SUCCESS;
}
