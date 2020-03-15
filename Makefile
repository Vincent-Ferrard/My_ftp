##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC		=	server/src/main.c			\
			server/src/server.c			\
			server/src/linked_list.c	\
			server/src/command.c		\
			server/src/data_command.c	\
			server/src/path_command.c	\
			server/src/user_command.c	\
			server/src/stwt.c

OBJ		=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS	=	-I ./server/inc/

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm
	make clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
