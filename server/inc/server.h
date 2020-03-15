/*
** EPITECH PROJECT, 2018
** server.h
** File description:
** server.h
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "linked_list.h"
#include "command.h"

void help_at_execute_time(void);

void init_sockaddr_in(struct sockaddr_in *, int);
void set_fd_select(int sockfd, fd_set *, list_t);
void connect_client(int, list_t *, int *, fd_set);
void read_client(fd_set, list_t *, int *);
void connection(int);
void my_ftp_server(char **);

int nb_args(char *, char);
char **stwt(char *, char);

#endif
