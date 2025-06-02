/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** main
*/

#include "../../include/serveur/my.h"

static void usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n team1 team2 "
        "-c clientNb -f freq\n    -p PORT -> port number\n    -x WIDTH -> "
        "width of the map\n    -y HEIGHT -> height of the map\n    -n TEAM1 "
        "TEAM2 ... -> names of teams\n    -c CLIENTNB -> number of clients "
        "per team\n    -f FREQ -> frequency of execution\n");
}

static void free_data(server_config_t *config)
{
    if (config->teams) {
        for (int i = 0; config->teams[i]; i++) {
            free(config->teams[i]);
        }
        free(config->teams);
    }
}

static bool init_config_end(server_config_t *config)
{
    config->teams_count = calloc(3, sizeof(int));
    if (!config->teams_count) {
        perror("Failed to allocate memory for team_count");
        return 1;
    }
    for (int i = 0; i < 3; i++)
        config->teams_count[i] = 0;
    config->client_nb = 2;
    config->team_nb = 3;
    config->freq = 100;
    return 0;
}

static bool init_config(server_config_t *config)
{
    config->port = 4242;
    config->width = 10;
    config->height = 10;
    config->teams = calloc(4, sizeof(char *));
    if (!config->teams) {
        perror("Failed to allocate memory for teams");
        return 1;
    }
    config->teams[0] = strdup("Epitech");
    config->teams[1] = strdup("Nancy");
    config->teams[2] = strdup("GRAPHIC");
    if (init_config_end(config))
        return 1;
    return 0;
}

bool fill_struct(server_config_t *config, char **av)
{
    if (strcmp(av[1], "--d") == 0)
        init_config(config);
    else if (parsing(av, config)) {
        usage();
        return true;
    }
    return 0;
}

static void debug(server_config_t *config)
{
    printf("Port: %d\n", config->port);
    printf("Width: %d\n", config->width);
    printf("Height: %d\n", config->height);
    printf("Client Number: %d\n", config->client_nb);
    printf("Frequency: %d\n", config->freq);
    if (config->teams) {
        printf("Teams:\n");
        for (int i = 0; config->teams[i]; i++) {
            printf("  - %s\n", config->teams[i]);
        }
    } else {
        printf("No teams defined.\n");
    }
}

int main(int ac, char **av)
{
    server_config_t config = {0};

    if (ac < 2 || strcmp(av[1], "--help") == 0) {
        usage();
        return EXIT_FAIL;
    }
    if (fill_struct(&config, av)) {
        free_data(&config);
        return EXIT_FAIL;
    }
    debug(&config);
    start_server(&config);
    free_data(&config);
    return EXIT_SUCCESS;
}
