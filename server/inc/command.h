/*
** EPITECH PROJECT, 2018
** command.h
** File description:
** command.h
*/

#ifndef COMMAND_H_
#define COMMAND_H_

int cmp_command(char *);
void switch_final_command(node_t *, char **, int);
void switch_other_command(list_t *, node_t *, char **, int);
void switch_command(list_t *, node_t *, int *, char *);
int is_not_log(node_t *);

void user(list_t *, node_t *, char *);
void pass(node_t *, char *);
void noop(node_t *);
void help(node_t *);
void quit(list_t *, int *, node_t *);

void cwd(node_t *, char *);
void cdup(node_t *, char *);
void cdup_change_to_parent_path(char *);
void pwd(node_t *);
void dele(node_t *, char *);

int init_socket_pasv(int, node_t *);
void print_pasv(node_t *, struct sockaddr_in);
void pasv(list_t *, int, node_t *);
char **init_file(FILE *);
void retr(node_t *, char *);

#endif
