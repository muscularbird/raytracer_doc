/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** log
*/

#include "../../include/serveur/my.h"
#include <sys/stat.h>

bool open_log_file(server_config_t *config)
{
    const char *log_dir = "./logs";
    const char *log_path = "./logs/zappy_serv.log";
    struct stat st = {0};

    if (stat(log_dir, &st) == -1) {
        if (mkdir(log_dir, 0755) == -1) {
            perror("Failed to create log directory");
            return true;
        }
    }
    config->log_file = fopen(log_path, "a");
    if (config->log_file == NULL) {
        perror("Failed to open log file");
        return true;
    }
    return false;
}

int write_log(FILE *log_file, const char *message, bool error)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char date_str[32];

    if (tm_info == NULL)
        return 0;
    strftime(date_str, sizeof(date_str), "[%Y-%m-%d %H:%M:%S]", tm_info);
    if (error)
        fprintf(log_file, "%s [ERROR] %s\n", date_str, message);
    else
        fprintf(log_file, "%s [INFO] %s\n", date_str, message);
    fflush(log_file);
    return 0;
}

void close_log_file(server_config_t *config)
{
    if (config->log_file != NULL)
        fclose(config->log_file);
}
