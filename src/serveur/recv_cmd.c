/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** recv_cmd
*/

#include "../../include/serveur/my.h"


char *extract_command(char *buffer)
{
    char *end = strstr(buffer, "\n");
    size_t cmd_len = 0;
    char *cmd = NULL;

    if (!end)
        return NULL;
    cmd_len = end - buffer;
    cmd = malloc(cmd_len + 1);
    if (!cmd)
        return NULL;
    strncpy(cmd, buffer, cmd_len);
    cmd[cmd_len] = '\0';
    return cmd;
}

void shift_buffer(char *buffer)
{
    char *end = strstr(buffer, "\n");

    if (!end)
        return;
    end += 1;
    memmove(buffer, end, strlen(end) + 1);
}

static void dispatch_command(serveur_t *serveur, int ind, const char *cmd,
    server_config_t *config)
{
    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strncmp(cmd, command_table[i].name,
            strlen(command_table[i].name)) == 0) {
            command_table[i].func(serveur, ind, cmd, config);
            return;
        }
    }
    send(serveur->client_list.clients[ind].fd, "Ko\n", 3, MSG_NOSIGNAL);
}

static void see_cmd(serveur_t *serveur, int index, server_config_t *config)
{
    char *cmd = extract_command(serveur->players->players[index].buff);

    if (cmd) {
        dispatch_command(serveur, index, cmd, config);
        free(cmd);
        shift_buffer(serveur->players->players[index].buff);
        see_cmd(serveur, index, config);
    } else
        return;
}

void recv_from_cli(serveur_t *serveur, int index, server_config_t *config)
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
