/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** login
*/

#include "../../include/serveur/my.h"

static bool timeout_check(serveur_t *serv, int ind, int fd, struct pollfd *pfd)
{
    int poll_ret = 0;

    poll_ret = poll(pfd, 1, 500);
    if (poll_ret == 0) {
        printf("Timeout waiting for client %d\n", fd);
        remove_client(serv, ind + 1);
        return true;
    }
    if (poll_ret < 0) {
        fprintf(stderr, "Poll error on client %d\n", fd);
        remove_client(serv, ind + 1);
        return true;
    }
    return false;
}

static char *rm_helper_client(serveur_t *serveur, int index, char *msg)
{
    int client_fd = serveur->client_list.clients[index].fd;

    if (msg)
        fprintf(stderr, "%s %d\n", msg, client_fd);
    remove_client(serveur, index + 1);
    return NULL;
}

static bool find_end_buf(char **end, char *buffer)
{
    *end = strstr(buffer, "\n");
    if (*end) {
        **end = '\0';
        return true;
    }
    return false;
}

char *read_log_data(serveur_t *serveur, int client_fd, int index)
{
    size_t total_read = 0;
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes = 0;
    char *end = NULL;
    struct pollfd pfd = { .fd = client_fd, .events = POLLIN };

    while (1) {
        if (timeout_check(serveur, index, client_fd, &pfd))
            return NULL;
        bytes = read(client_fd, buffer + total_read, sizeof(buffer) - 1
        - total_read);
        if (bytes <= 0)
            return rm_helper_client(serveur, index, "Error reading");
        total_read += bytes;
        if (find_end_buf(&end, buffer))
            break;
        if (total_read >= sizeof(buffer) - 2)
            return rm_helper_client(serveur, index, "Buffer overflow");
    }
    return strdup(buffer);
}

void validate_team_name(int index, char *buf, serveur_t *serv,
    server_config_t *conf)
{
    char cli_s[48] = {0};
    int client_fd = serv->players->players[index].fd + 1;
    int found = 0;

    serv->players->players[index + 1].team_name = buf;
    for (int t = 0; t < conf->team_nb; t++) {
        if (strcmp(buf, conf->teams[t]) == 0) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Invalid team name from client %d: %s\n", client_fd, buf);
        send(client_fd, "KO\n", 3, MSG_NOSIGNAL);
        remove_client(serv, index + 1);
        return;
    }
    conf->teams_count[find_index_team(conf, buf)]++;
    sprintf(cli_s, "%d\n%d %d\n", conf->client_nb, conf->width, conf->height);
    send(client_fd, cli_s, strlen(cli_s), MSG_NOSIGNAL);
}

void send_log_info(serveur_t *serveur, server_config_t *config)
{
    int client_fd = accept(serveur->server_fd, NULL, NULL);
    int index = find_index(serveur, client_fd - 1);
    char *buffer = NULL;

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
    buffer = read_log_data(serveur, client_fd, index);
    if (!buffer)
        return;
    validate_team_name(index, buffer, serveur, config);
}
