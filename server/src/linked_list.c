/*
** EPITECH PROJECT, 2018
** linked_list.c
** File description:
** linked_list.c
*/

#include "server.h"

void add_node(list_t *list, int sockfd, char *type, struct sockaddr_in sockin)
{
    node_t *node = malloc(sizeof(node_t));

    node->sockfd = sockfd;
    node->data_sockfd = -1;
    node->type = type;
    node->sockin = sockin;
    node->login = NULL;
    node->passwd = NULL;
    node->file = fdopen(sockfd, "r");
    node->next = *list;
    if (*list != NULL)
        *list = node;
    else
        *list = node;
}

void delete_node(list_t *list, int sockfd)
{
    list_t ptr = *list;

    if (ptr == NULL)
        return;
    if (ptr->sockfd == sockfd) {
        if (ptr->next == NULL)
            *list = NULL;
        else
            *list = (*list)->next;
        return;
    }
    while (ptr) {
        if (ptr->next->sockfd == sockfd) {
            ptr->next = ptr->next->next;
            break;
        }
        ptr = ptr->next;
    }
    list = &ptr;
}

int get_list_max(list_t list)
{
    int most = 0;

    while (list) {
        most = list->sockfd > most ? list->sockfd : most;
        list = list->next;
    }
    return (most);
}

int get_list_size(list_t list)
{
    int i = 0;

    for (int i = 0; list; i++)
        list = list->next;
    return (i - 1);
}

void set_data_sockfd(list_t *list, int sockfd, int data_sockfd)
{
    list_t ptr = *list;

    while (ptr) {
        if (ptr->sockfd == sockfd)
            ptr->data_sockfd = data_sockfd;
        ptr = ptr->next;
    }
    list = &ptr;
}
