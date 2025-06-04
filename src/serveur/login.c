/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** login
*/

#include "../../include/serveur/my.h"

static bool validate_nb_players(server_config_t *conf, int index,
    server_t *serv, const char *buf)
{
    char cli_s[48] = {0};
    int client_fd = serv->players->players[index].fd;
    int pos = find_index_team(conf, buf);

    if (conf->teams_count_connect[pos] == conf->teams_count_max[pos]) {
        printf("This teams is already full %d: %s\n", client_fd, buf);
        send(client_fd, "KO\n", 3, MSG_NOSIGNAL);
        return true;
    }
    conf->teams_count_connect[pos]++;
    sprintf(cli_s, "%d\n%d %d\n", conf->client_nb, conf->width, conf->height);
    send(client_fd, cli_s, strlen(cli_s), MSG_NOSIGNAL);
    return false;
}

int validate_log_info(const char *buf, server_t *serv,
    server_config_t *conf, int index)
{
    bool found = false;

    for (int i = 0; i < conf->team_nb; i++) {
        if (strcmp(buf, conf->teams[i]) == 0) {
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Invalid team name from client %d: %s\n",
            serv->players->players[index].fd, buf);
        send(serv->players->players[index].fd, "KO\n", 3, MSG_NOSIGNAL);
        return 1;
    }
    if (validate_nb_players(conf, index, serv, buf))
        return 1;
    return 0;
}

void send_log_info(server_t *serveur)
{
    int client_fd = accept(serveur->server_fd, NULL, NULL);
    int index = find_index(serveur, client_fd - 1);

    if (client_fd < 0) {
        fprintf(stderr, "Error accept");
        return;
    }
    if (index == -1) {
        close(client_fd);
        return;
    }
    add_client(serveur, client_fd);
    send(client_fd, "WELCOME\n", 9, MSG_NOSIGNAL);
}
