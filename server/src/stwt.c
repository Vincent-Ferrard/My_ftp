/*
** EPITECH PROJECT, 2018
** stwt.c
** File description:
** stwt.c
*/

#include "server.h"

int nb_args(char *str, char c)
{
    int nbr_args = 1;

    if (str == NULL)
        return (1);
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            nbr_args++;
    return (nbr_args + 1);
}

char **stwt(char *str, char c)
{
    char **interact = malloc(sizeof(char *) * nb_args(str, c));
    int j = 0;
    int k = 0;

    if (str == NULL)
        return (NULL);
    for (int h = 0; h < nb_args(str, c); h++)
        interact[h] = malloc(sizeof(char) * (strlen(str) + 1));
    for (int i = 0; str[i] && str[i] != '\n'; i++)
        if (str[i] == c) {
            interact[j][k] = '\0';
            j++;
            k = 0;
        } else {
            interact[j][k] = str[i];
            k++;
        }
    interact[j][k] = '\0';
    interact[j + 1] = NULL;
    return (interact);
}
