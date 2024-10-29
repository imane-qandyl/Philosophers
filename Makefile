# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 07:24:27 by imqandyl          #+#    #+#              #
#    Updated: 2024/10/21 09:45:32 by imqandyl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

SRC = main.c utils.c routine.c initialize.c
OBJ = $(SRC:.c=.o)

PATH_SRC = ./src/
SRC_FILES = $(addprefix $(PATH_SRC), $(SRC))
OBJ_FILES = $(addprefix $(PATH_SRC), $(OBJ))

CFLAGS = -Wall -Wextra -Werror -O3 -pthread -I./include
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
 #re debug

# debug: FLAGS += -g
# debug: re

# delay:
# 	python3 delay_o_meter.py