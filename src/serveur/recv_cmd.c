/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** recv_cmd
*/

#include "../../include/serveur/my.h"


char *extract_command(char *buffer)
{
    char *end = strstr(buffer, "\r\n");
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
    char *end = strstr(buffer, "\r\n");

    if (!end)
        return;
    end += 2;
    memmove(buffer, end, strlen(end) + 1);
}

static void see_cmd(serveur_t *serveur, int index)
{
    char *cmd = extract_command(serveur->players->players[index].buff);

    if (cmd) {
        printf("Received from client %d: %s\n",
            serveur->client_list.clients[index].fd, cmd);
        free(cmd);
        shift_buffer(serveur->players->players[index].buff);
        printf("Buffer after shift: %s\n",
            serveur->players->players[index].buff);
        see_cmd(serveur, index);
    } else
        return;
}

void recv_from_cli(serveur_t *serveur, int index)
{
    char buf[BUFFER_SIZE] = {0};
    int bytes_read = recv(serveur->client_list.clients[index].fd, buf,
        sizeof(buf) - 1, 0);

    if (bytes_read <= 0 && remove_client(serveur, index))
        return;
    buf[bytes_read] = '\0';
    strncat(serveur->players->players[index].buff, buf,
        BUFFER_SIZE - strlen(serveur->players->players[index].buff) - 1);
    see_cmd(serveur, index);
}
