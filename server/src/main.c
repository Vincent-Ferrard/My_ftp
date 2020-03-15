/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main.c
*/

#include "server.h"

void init_sockaddr_in(struct sockaddr_in *sockin, int port)
{
    sockin->sin_family = AF_INET;
    sockin->sin_port = htons(port);
    sockin->sin_addr.s_addr = INADDR_ANY;
}

void help_at_execute_time(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    printf("\tpath\tis the path to the home directory for ");
    printf("the Anonymous user\n");
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        help_at_execute_time();
        return (0);
    } else if (ac != 3) {
        write(2, "Error: Bad number of arguments.\n", 32);
        return (84);
    }
    if (chdir(av[2]) == -1) {
        write(2, "Error: Invalid path.\n", 21);
        return (84);
    }
    my_ftp_server(av);
    return (0);
}
