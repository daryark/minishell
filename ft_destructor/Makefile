# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 14:20:53 by escura            #+#    #+#              #
#    Updated: 2024/06/03 20:49:27 by dyarkovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS	= ft_destructors.o ft_allocs.o ft_utils.o ft_init.o
SOURCE	= ft_destructors.c ft_allocs.c ft_utils.c ft_init.c
HEADER	= ft_alloc.h
OUT	= ft_alloc.a
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror
LFLAGS	 = 

all: $(OUT)

$(OUT): $(OBJS) $(HEADER)
	ar rcs $(OUT) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OUT)

re: fclean all

.PHONY: all clean fclean