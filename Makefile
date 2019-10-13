# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpole <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 10:08:31 by bpole             #+#    #+#              #
#    Updated: 2019/10/13 12:59:02 by bpole            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIB = ./libft/libft.a

SRC = ./main.c ./fillit.c

OBJ = $(SRC:.c=.o)

INCLUDE = ./

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC) -I $(INCLUDE)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
