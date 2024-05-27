# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 22:05:48 by btvildia          #+#    #+#              #
#    Updated: 2024/05/27 22:09:25 by btvildia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_class.a
HEADER	= ft_class.h
OBJ	= $(SRC:.c=.o)
SRC	= ft_utils.c ft_class.c ft_attributes.c ft_get.c
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror
LFLAGS	 = 

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
