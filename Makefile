# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 07:24:27 by imqandyl          #+#    #+#              #
#    Updated: 2024/11/02 21:00:13 by imqandyl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c routine.c initialize.c utils2.c
OBJ = $(SRC:.c=.o)

PATH_SRC = ./src/
SRC_FILES = $(addprefix $(PATH_SRC), $(SRC))
OBJ_FILES = $(addprefix $(PATH_SRC), $(OBJ))

CFLAGS = -Wall -Wextra -Werror -g -pthread -I./include
CC = gcc

HEADER = ./include/philosopher.h

all: $(NAME)

$(NAME): $(OBJ_FILES) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

$(PATH_SRC)%.o: $(PATH_SRC)%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
