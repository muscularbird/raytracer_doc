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
    if (config->teams_count_max)
        free(config->teams_count_max);
    if (config->teams_count_connect)
        free(config->teams_count_connect);
}

static bool init_config_end(server_config_t *config)
{
    config->teams_count_max = calloc(3, sizeof(int));
    config->teams_count_connect = calloc(3, sizeof(int));
    if (!config->teams_count_max || !config->teams_count_connect) {
        write_log(config->log_file, "Memory allocation failed for team_count",
            true);
        return 1;
    }
    config->client_nb = 2;
    for (int i = 0; i < 3; i++) {
        config->teams_count_max[i] = config->client_nb;
        config->teams_count_connect[i] = 0;
    }
    config->team_nb = 3;
    config->freq = 100;
    return 0;
}

static bool init_config(server_config_t *conf)
{
    conf->port = 4242;
    conf->width = 10;
    conf->height = 10;
    conf->debug = true;
    conf->teams = calloc(4, sizeof(char *));
    if (!conf->teams) {
        write_log(conf->log_file, "Memory allocation failed for teams", true);
        return 1;
    }
    conf->teams[0] = strdup("Epitech");
    conf->teams[1] = strdup("Nancy");
    conf->teams[2] = strdup("GRAPHIC");
    if (init_config_end(conf))
        return 1;
    return 0;
}

bool fill_struct(server_config_t *config, char **av)
{
    if (strcmp(av[1], "--d") == 0) {
        if (init_config(config))
            return true;
    } else if (parsing(av, config)) {
        usage();
        return true;
    }
    return 0;
}

static void print_parsing(server_config_t *config)
{
    char buffer[BUFFER_SIZE] = {0};

    snprintf(buffer, sizeof(buffer), "Port: %d, Width: %d, Height: %d, "
        "Client Number: %d, Frequency: %d", config->port, config->width,
        config->height, config->client_nb, config->freq);
    write_log(config->log_file, "Configuration details:", false);
    write_log(config->log_file, buffer, false);
    write_log(config->log_file, "Teams:", false);
    for (int i = 0; config->teams[i]; i++) {
        memset(buffer, 0, sizeof(buffer));
        snprintf(buffer, sizeof(buffer), "   - %s", config->teams[i]);
        write_log(config->log_file, buffer, false);
    }
}

int main(int ac, char **av)
{
    server_config_t config = {0};

    if (open_log_file(&config))
        return EXIT_FAIL;
    if (ac < 2 || strcmp(av[1], "--help") == 0) {
        usage();
        return EXIT_FAIL;
    }
    if (fill_struct(&config, av)) {
        free_data(&config);
        return EXIT_FAIL;
    }
    if (config.debug)
        print_parsing(&config);
    start_server(&config);
    free_data(&config);
    close_log_file(&config);
    return EXIT_SUCCESS;
}
