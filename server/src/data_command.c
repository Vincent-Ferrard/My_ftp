/*
** EPITECH PROJECT, 2018
** data_command.c
** File description:
** data_command.c
*/

#include "server.h"

int init_socket_pasv(int dsockfd, node_t *client)
{
    if (dsockfd == -1) {
        write(client->sockfd, "425 Error: Pasv error.\n", 23);
        return (-1);
    }
    return (0);
}

void print_pasv(node_t *client, struct sockaddr_in dsockin)
{
    char *line;
    int size = strlen(inet_ntoa(dsockin.sin_addr)) + 6;

    size += (int) log10((double) ntohs(dsockin.sin_port));
    line = malloc(sizeof(char) * size);
    sprintf(line, "227 %s", inet_ntoa(dsockin.sin_addr));
    sprintf(line, "%s:%d\n", line, ntohs(dsockin.sin_port));
    write(client->sockfd, line, strlen(line));
}

void pasv(list_t *list, int csockfd, node_t *client)
{
    int dsockfd;
    struct sockaddr_in dsockin;
    char *line;
    int size;

    if (is_not_log(client) == 0)
        return;
    dsockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (init_socket_pasv(dsockfd, client) == -1)
        return;
    init_sockaddr_in(&dsockin, 4241 + 256);
    dsockin.sin_addr.s_addr = client->sockin.sin_addr.s_addr;
    if (bind(dsockfd, (struct sockaddr *) &dsockin, sizeof(dsockin)) == -1) {
        write(client->sockfd, "425 Error: Pasv error.\n", 23);
        return;
    }
    print_pasv(client, dsockin);
    set_data_sockfd(list, csockfd, dsockfd);
}

char **init_file(FILE *fd)
{
    char **file;
    char *s;
    size_t n;
    int i;

    file = malloc(sizeof(char *));
    for (i = 0; getline(&s, &n, fd) != -1; i++) {
        file[i] = strdup(s);
        file = realloc(file, sizeof(char *) * (i + 2));
    }
    file[i] = NULL;
    return (file);
}

void retr(node_t *client, char *path)
{
    FILE *fd;
    char **file;

    if (is_not_log(client) == 0)
        return;
    if (path == NULL) {
        write(client->sockfd, "501 Error: invalid path.\n", 25);
        return;
    }
    fd = fopen(path, "r");
    if (fd == NULL) {
        write(client->sockfd, "501 Error: invalid path.\n", 25);
        return;
    }
    file = init_file(fd);
    fclose(fd);
    write(client->sockfd, "150 File status okay; for data connection.\n", 43);
    for (int i = 0; file[i]; i++)
        free(file[i]);
    free(file);
}
