/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** login
*/

#include "../../include/serveur/my.h"

static void send_content_of_tile(server_t *serv, server_config_t *conf,
    int fd, int y)
{
    char buff[BUFFER_SIZE] = {0};
    char tmp[16] = {0};

    for (int x = 0; x < conf->width; x++) {
        snprintf(buff, sizeof(buff), "bct %d %d", x, y);
        for (enum obj_type obj = 0; obj < LAST_OBJECT; obj++) {
            memset(tmp, 0, sizeof(tmp));
            snprintf(tmp, sizeof(tmp), " %d", serv->map[y][x].ressources[obj]);
            strncat(buff, tmp, sizeof(buff) - strlen(buff) - 1);
        }
        strncat(buff, "\n", sizeof(buff) - strlen(buff) - 1);
        send(fd, buff, strlen(buff), MSG_NOSIGNAL);
        memset(buff, 0, sizeof(buff));
    }
}

static void send_welcome_graphic(server_t *serv, server_config_t *conf, int fd)
{
    char buff[BUFFER_SIZE] = {0};

    snprintf(buff, sizeof(buff), "msz %d %d\n", conf->width, conf->height);
    send(fd, buff, strlen(buff), MSG_NOSIGNAL);
    memset(buff, 0, sizeof(buff));
    snprintf(buff, sizeof(buff), "sgt %d\n", conf->freq);
    for (int y = 0; y < conf->height; y++)
        send_content_of_tile(serv, conf, fd, y);
}

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
    if (strcmp(buf, "GRAPHIC") == 0) {
        serv->players->players[index].isGUI = true;
        send_welcome_graphic(serv, conf, client_fd);
        return false;
    } else
        init_pos_player(serv->players->players, index, conf);
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

void send_log_info(server_t *serveur, server_config_t *config)
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
    add_client(serveur, client_fd, config);
    send(client_fd, "WELCOME\n", 9, MSG_NOSIGNAL);
}
