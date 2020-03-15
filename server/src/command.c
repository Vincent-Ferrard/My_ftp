/*
** EPITECH PROJECT, 2018
** command.c
** File description:
** command.c
*/

#include "server.h"

char *cmd[] = {
    "USER",
    "PASS",
    "CWD",
    "CDUP",
    "PWD",
    "DELE",
    "PASV",
    "RETR",
    "NOOP",
    "HELP",
    "QUIT",
    NULL,
};

int cmp_command(char *s)
{
    for (int i = 0; cmd[i]; i++)
        if (strcmp(s, cmd[i]) == 0)
            return (i);
    return (-1);
}

void switch_final_command(node_t *ptr, char **all_cmd, int cmp)
{
    switch (cmp) {
        case 7:
            retr(ptr, all_cmd[1]);
            break;
        case 8:
            noop(ptr);
            break;
        case 9:
            help(ptr);
            break;
        default:
            write(ptr->sockfd, "500 Error: non valid command.\n", 30);
    }
}

void switch_other_command(list_t *list, node_t *ptr, char **all_cmd, int cmp)
{
    switch (cmp) {
        case 2:
            cwd(ptr, all_cmd[1]);
            break;
        case 3:
            cdup(ptr, all_cmd[1]);
            break;
        case 4:
            pwd(ptr);
            break;
        case 5:
            dele(ptr, all_cmd[1]);
            break;
        case 6:
            pasv(list, ptr->sockfd, ptr);
            break;
        default:
            switch_final_command(ptr, all_cmd, cmp);
    }
}

void switch_command(list_t *list, node_t *ptr, int *max_sockfd, char *s)
{
    char **all_cmd = stwt(s, ' ');
    int cmp = cmp_command(all_cmd[0]);

    switch (cmp) {
        case 0:
            user(list, ptr, all_cmd[1]);
            break;
        case 1:
            pass(ptr, all_cmd[1]);
            break;
        case 10:
            quit(list, max_sockfd, ptr);
            break;
        default:
            switch_other_command(list, ptr, all_cmd, cmp);
    }
    for (int i = 0; all_cmd[i]; i++)
        free(all_cmd[i]);
    free(all_cmd);
}

int is_not_log(node_t *client)
{
    if (client->passwd == NULL) {
        write(client->sockfd, "530 Error: Not logged in.\n", 26);
        return (0);
    }
    return (1);
}
