/*
** EPITECH PROJECT, 2018
** path_command.c
** File description:
** path_command.c
*/

#include "server.h"

void cwd(node_t *client, char *path)
{
    if (is_not_log(client) == 0)
        return;
    if (path == NULL)
        write(client->sockfd, "550 Error: no path.\n", 20);
    else {
        if (chdir(path) == -1)
            write(client->sockfd, "550 Error: path doesn't exist.\n", 31);
        else
            write(client->sockfd, "250 Requested file action okay.\n", 32);
    }
}

void cdup(node_t *client, char *other)
{
    int size = (int) pathconf(".", _PC_PATH_MAX);
    char *path = malloc(sizeof(char) * size);

    if (is_not_log(client) == 0)
        return;
    if (other != NULL) {
        write(client->sockfd, "501 Error: not valid instruction.\n", 34);
        return;
    }
    path = getcwd(path, size);
    if (path == NULL) {
        write(client->sockfd, "550 Error: invalid path.\n", 25);
        return;
    }
    cdup_change_to_parent_path(path);
    if (chdir(path) == -1)
        write(client->sockfd, "550 Error: path doesn't exist.\n", 31);
    else
        write(client->sockfd, "200 Command okay.\n", 18);
    free(path);
}

void cdup_change_to_parent_path(char *path)
{
    int i;
    int count = 0;

    if (strcmp(path, "/") != 0) {
        for (i = 0; path[i]; i++)
            if (path[i] == '/')
                count++;
        for (i = 0; count > 0; i++)
            if (path[i] == '/')
                count--;
        path[i] = '\0';
    }
}

void pwd(node_t *client)
{
    int size = (int) pathconf(".", _PC_PATH_MAX);
    char *path;
    char *line;

    if (is_not_log(client) == 0)
        return;
    path = malloc(sizeof(char) * size);
    path = getcwd(path, size);
    if (path == NULL)
        write(client->sockfd, "550 Error: pwd.\n", 15);
    else {
        line = malloc(sizeof(char) * (size + 14));
        sprintf(line, "257 %s created.\n", path);
        write(client->sockfd, line, strlen(line));
        free(line);
    }
    free(path);
}

void dele(node_t *c, char *path)
{
    if (is_not_log(c) == 0)
        return;
    if (path == NULL) {
        write(c->sockfd, "501 Error: no path.\n", 20);
        return;
    }
    if (remove(path) == -1)
        write(c->sockfd, "550 Error: invalid path.\n", 25);
    else
        write(c->sockfd, "250 Requested file action okay, completed.\n", 43);
}
