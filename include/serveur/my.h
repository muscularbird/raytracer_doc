/*
** EPITECH PROJECT, 2025
** zapp
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    #define EXIT_FAIL 84
    #define EXIT_SUCCESS 0

typedef struct server_config_s {
    int port;
    int width;
    int height;
    char **teams;
    int client_nb;
    int freq;
} server_config_t;

bool parsing(char **av, server_config_t *config);

#endif /* !MY_H_ */
