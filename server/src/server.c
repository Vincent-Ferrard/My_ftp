/*
** EPITECH PROJECT, 2018
** server.c
** File description:
** server.c
*/

#include "server.h"

void set_fd_select(int sockfd, fd_set *rdfs, list_t list)
{
    FD_ZERO(rdfs);
    FD_SET(sockfd, rdfs);
    while (list) {
        FD_SET(list->sockfd, rdfs);
        list = list->next;
    }
}

void connect_client(int sockfd, list_t *list, int *max_sockfd, fd_set rdfs)
{
    struct sockaddr_in csockin;
    socklen_t csocksize = sizeof(csockin);
    int csockfd;

    csockfd = accept(sockfd, (struct sockaddr *) &csockin, &csocksize);
    if (csockfd != -1) {
        write(csockfd, "220 Service ready for new user.\n", 32);
        printf("Connection from %s\n", inet_ntoa(csockin.sin_addr));
        *max_sockfd = csockfd > *max_sockfd ? csockfd : *max_sockfd;
        add_node(list, csockfd, "client", csockin);
    } else
        printf("Connection error!\n");
}

void read_client(fd_set rdfs, list_t *list, int *max_sockfd)
{
    list_t ptr = *list;
    int nb_bytes;
    char *s;
    size_t n;

    while (ptr) {
        if (FD_ISSET(ptr->sockfd, &rdfs)) {
            s = NULL;
            nb_bytes = getline(&s, &n, ptr->file);
            if (nb_bytes > 0) {
                s[strlen(s) - 2] = '\0';
                printf("Client %d said : \"%s\" \n", ptr->sockfd, s);
                switch_command(list, ptr, max_sockfd, s);
            } else if (nb_bytes <= 0)
                quit(list, max_sockfd, ptr);
            free(s);
            break;
        }
        ptr = ptr->next;
    }
}

void connection(int sockfd)
{
    static int max_sockfd = 0;
    static list_t list = NULL;
    fd_set rdfs;

    set_fd_select(sockfd, &rdfs, list);
    if (max_sockfd == 0)
        max_sockfd = sockfd;
    if (select(max_sockfd + 1, &rdfs, NULL, NULL, NULL) == -1) {
        printf("Err: select\n");
        exit(84);
    } else {
        if (FD_ISSET(sockfd, &rdfs))
            connect_client(sockfd, &list, &max_sockfd, rdfs);
        else
            read_client(rdfs, &list, &max_sockfd);
    }
}

void my_ftp_server(char **av)
{
    struct sockaddr_in sockin;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("Err: socket\n");
        exit(84);
    }
    init_sockaddr_in(&sockin, atoi(av[1]));
    if (bind(sockfd, (struct sockaddr *) &sockin, sizeof(sockin)) == -1) {
        printf("Err: bind\n");
        exit(84);
    }
    if (listen(sockfd, 5) == -1) {
        printf("Err: listen\n");
        exit(84);
    }
    while (1)
        connection(sockfd);
    close(sockfd);
}
