/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** *
*/

#include "../../include/serveur/my.h"

static bool parse_flag(server_config_t *config, char **av, int *i)
{
    if (av[*i] && av[*i + 1] && strcmp(av[*i], "-p") == 0) {
        config->port = atoi(av[*i + 1]);
        *i += 2;
        return false;
    } else if (av[*i] && av[*i + 1] && strcmp(av[*i], "-x") == 0) {
        config->width = atoi(av[*i + 1]);
        *i += 2;
        return false;
    }
    if (av[*i] && av[*i + 1] && strcmp(av[*i], "-c") == 0) {
        config->client_nb = atoi(av[*i + 1]);
        *i += 2;
        return false;
    } else if (av[*i] && av[*i + 1] && strcmp(av[*i], "-f") == 0) {
        config->freq = atoi(av[*i + 1]);
        *i += 2;
        return false;
    }
    return true;
}

static bool flag_n_scpart(server_config_t *config, int temporary)
{
    free(config->teams[temporary - 1]);
    config->teams[temporary - 1] = strdup("GRAPHIC");
    if (!config->teams[temporary - 1])
        return true + 0 * fprintf(stderr, "Memory alloc failed\n");
    config->teams[temporary] = NULL;
    config->team_nb = temporary;
    config->teams_count_max = calloc(temporary, sizeof(int));
    config->teams_count_connect = calloc(temporary, sizeof(int));
    if (!config->teams_count_max || !config->teams_count_connect) {
        perror("Failed to allocate memory for team_count");
        return 1;
    }
    for (int i = 0; i < temporary; i++) {
        config->teams_count_max[i] = config->client_nb;
        config->teams_count_connect[i] = 0;
    }
    return false;
}

static bool flag_n(int *i, char **av, server_config_t *config)
{
    int j = 0;
    int temporary = 1;

    (*i)++;
    j = *i;
    while (av[*i] && av[*i][0] != '-') {
        temporary++;
        (*i)++;
    }
    config->teams = calloc(temporary + 1, sizeof(char *));
    if (!config->teams)
        return true + 0 * fprintf(stderr, "Memory alloc failed\n");
    for (int k = 0; k < temporary; k++) {
        config->teams[k] = strdup(av[j + k]);
        if (!config->teams[k])
            return true + 0 * fprintf(stderr, "Memory alloc failed\n");
    }
    if (flag_n_scpart(config, temporary))
        return true;
    return false;
}

bool parse_all_flag(char **av, server_config_t *config, int *i)
{
    bool error = true;

    error = parse_flag(config, av, i);
    if (av[*i] && av[*i + 1] && strcmp(av[*i], "-y") == 0) {
        config->height = atoi(av[*i + 1]);
        *i += 2;
        error = false;
    } else if (av[*i] && strcmp(av[*i], "-n") == 0) {
        error = flag_n(i, av, config);
    }
    if (error)
        return true + 0 * fprintf(stderr, "Invalid argument:\n");
    return false;
}

bool parsing(char **av, server_config_t *config)
{
    int i = 1;

    while (av[i]) {
        if (parse_all_flag(av, config, &i))
            return true;
    }
    if (config->port <= 0 || config->height <= 0 ||
        config->width <= 0 || config->client_nb <= 0 || config->freq <= 0) {
        fprintf(stderr, "Invalid configuration values.\n");
        return true;
    }
    return false;
}
