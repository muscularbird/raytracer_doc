/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** recv_cmd
*/

#include "../../include/serveur/my.h"

static void dispatch_command(server_t *serveur, int ind, const char *cmd,
    server_config_t *config)
{
    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strncmp(cmd, command_table[i].name,
            strlen(command_table[i].name)) == 0) {
            command_table[i].func(serveur, ind, cmd, config);
            serveur->players->players[ind].nb_bad_cmd = 0;
            return;
        }
    }
    send(serveur->client_list.clients[ind].fd, KO_CMD, 3, MSG_NOSIGNAL);
    serveur->players->players[ind].nb_bad_cmd++;
    if (serveur->players->players[ind].nb_bad_cmd >= 10) {
        fprintf(stderr, "Client %d send to many bad request\n",
            serveur->players->players[ind].fd);
        remove_client(serveur, ind);
    } else
        fprintf(stderr, "Bad command from client %d: %s\n",
            serveur->players->players[ind].fd, cmd);
}

int find_team(char **cmd, server_t *serv, server_config_t *config, int index)
{
    printf("%s\n", *cmd);
    if (!serv->players->players[index].is_loged) {
        if (validate_log_info(*cmd, serv, config, index)) {
            free(*cmd);
            remove_client(serv, index);
            return 1;
        } else
            serv->players->players[index].team_name = strdup(*cmd);
        serv->players->players[index].is_loged = true;
    } else
        dispatch_command(serv, index, *cmd, config);
    return 0;
}

// see_cmd(serveur, index, config);
static void see_cmd(server_t *serveur, int index, server_config_t *config)
{
    char *cmd = extract_command(serveur->players->players[index].buff);

    if (cmd) {
        if (find_team(&cmd, serveur, config, index))
            return;
        free(cmd);
        shift_buffer(serveur->players->players[index].buff);
        serveur->players->players[index].req_without_answer = 0;
    } else {
        serveur->players->players[index].req_without_answer++;
        if (serveur->players->players[index].req_without_answer >= 10) {
            fprintf(stderr, "Client %d send to many request without answer\n",
                serveur->players->players[index].fd);
            remove_client(serveur, index);
        }
        return;
    }
}

void recv_from_cli(server_t *serveur, int index, server_config_t *config)
{
    char buf[BUFFER_SIZE] = {0};
    int bytes_read = recv(serveur->client_list.clients[index].fd, buf,
        sizeof(buf) - 1, 0);

    if (bytes_read <= 0 && remove_client(serveur, index))
        return;
    buf[bytes_read] = '\0';
    strncat(serveur->players->players[index].buff, buf,
        BUFFER_SIZE - strlen(serveur->players->players[index].buff) - 1);
    see_cmd(serveur, index, config);
}
