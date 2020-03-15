/*
** EPITECH PROJECT, 2018
** user_command.c
** File description:
** user_command.c
*/

#include "server.h"

void user(list_t *list, node_t *client, char *login)
{
    if (login == NULL) {
        write(client->sockfd, "530 Error: waiting login.\n", 26);
        return;
    }
    client->login = strdup(login);
    write(client->sockfd, "331 User name okay, need password.\n", 35);
}

void pass(node_t *client, char *passwd)
{
    if (passwd == NULL) {
        write(client->sockfd, "530 Error: waiting password.\n", 29);
        return;
    }
    if (client->login == NULL || strcmp(client->login, "Anonymous") != 0)
        write(client->sockfd, "530 Error: need login.\n", 23);
    else {
        client->passwd = strdup(passwd);
        write(client->sockfd, "230 User logged in, proceed.\n", 29);
    }
}

void noop(node_t *client)
{
    if (is_not_log(client) == 0)
        return;
    write(client->sockfd, "200 Command okay\n", 17);
}

void help(node_t *client)
{
    if (is_not_log(client) == 0)
        return;
    write(client->sockfd, "214 Help message.\n", 18);
}

void quit(list_t *list, int *max_sockfd, node_t *client)
{
    printf("Client disconnected\n");
    if (client->passwd != NULL && client->login != NULL)
        write(client->sockfd, "221 Logged out.\n", 16);
    else
        write(client->sockfd, "221 Service closing control connection.\n", 40);
    close(client->sockfd);
    if (client->data_sockfd != -1)
        close(client->data_sockfd);
    delete_node(list, client->sockfd);
    *max_sockfd = get_list_max(*list);
}
