/*
** EPITECH PROJECT, 2018
** linked_list.h
** File description:
** linked_list.h
*/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct node_s {
    int sockfd;
    int data_sockfd;
    char *type;
    struct sockaddr_in sockin;
    char *login;
    char *passwd;
    FILE *file;
    struct node_s *next;
} node_t;

typedef node_t * list_t;

void add_node(list_t *, int, char *, struct sockaddr_in);
void delete_node(list_t *, int);
int get_list_max(list_t);
int get_list_size(list_t);
void set_data_sockfd(list_t *, int, int);

#endif
