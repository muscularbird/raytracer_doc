/*
** EPITECH PROJECT, 2025
** zappy_mirroring
** File description:
** map_handling
*/

#include "../../include/serveur/my.h"

static double find_density(enum obj_type type)
{
    switch (type) {
        case FOOD:
            return FOOD_DENSITY;
        case LINEMATE:
            return LINEMATE_DENSITY;
        case DERAUMERE:
            return DERAUMERE_DENSITY;
        case SIBUR:
            return SIBUR_DENSITY;
        case MENDIANE:
            return MENDIANE_DENSITY;
        case PHIRAS:
            return PHIRAS_DENSITY;
        case THYSTAME:
            return THYSTAME_DENSITY;
        default:
            return 0.0f;
    }
}

static void place_correct_obj(server_t *serv, int obj, int x, int y)
{
    serv->map[y][x].ressources[obj]++;
}

static void place_objects(int obj, server_t *serv,
    server_config_t *config, int nb_objects)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < nb_objects; i++) {
        x = rand() % config->width;
        y = rand() % config->height;
        place_correct_obj(serv, obj, x, y);
    }
}

void dispatch_objects(server_t *serv, server_config_t *config)
{
    int nb_objects = 0;
    double multiplicator = 0;

    srand(time(NULL));
    for (enum obj_type obj = 0; obj < LAST_OBJECT; obj++) {
        multiplicator = find_density(obj);
        nb_objects = config->width * config->height * multiplicator;
        place_objects(obj, serv, config, nb_objects);
    }
}

static void display_item_of_tile(server_t *serv, int i, int j)
{
    for (int k = 0; k < LAST_OBJECT; k++) {
        printf("Tile (%d, %d) has %d of type %d\n",
            j, i, serv->map[i][j].ressources[k], k);
    }
}

void print_map(server_t *serv, server_config_t *config)
{
    printf("Map (%d x %d):\n", config->width, config->height);
    for (int i = 0; i < config->height; i++) {
        for (int j = 0; j < config->width; j++) {
            printf("Initializing tile at (%d, %d)\n", j, i);
            display_item_of_tile(serv, i, j);
        }
    }
}

static bool place_on_map(server_t *serv, server_config_t *config, int i)
{
    for (int j = 0; j < config->width; j++) {
        serv->map[i][j].ressources = calloc(sizeof(int), LAST_OBJECT);
        if (!serv->map[i][j].ressources)
            return true;
    }
    return false;
}

int generate_map(server_t *serv, server_config_t *config)
{
    serv->map = calloc(sizeof(tile_t *), config->height + 1);
    if (!serv->map)
        return EXIT_FAIL;
    for (int i = 0; i < config->height; i++) {
        serv->map[i] = calloc(sizeof(tile_t), config->width + 1);
        if (!serv->map[i])
            return EXIT_FAIL;
    }
    for (int i = 0; i < config->height; i++) {
        if (place_on_map(serv, config, i))
            return EXIT_FAIL;
    }
    dispatch_objects(serv, config);
    if (config->debug)
        print_map(serv, config);
    return EXIT_SUCCESS;
}
