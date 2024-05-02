NAME = minishell

CFLAGS = -Wall -Wextra -Werror 
LFLAGS = -lreadline
CC = cc
HEADERS = incl/minishell.h incl/execute.h incl/sources.h

SRC =	minishell.c \
		execute.c \
		execute2.c \
		parsing.c \
		source1.c \
		utils.c \

SRC_F = src/
OBJ_F = obj/
VPATH = $(SRC_F) $(SRC_F)exec/ $(SRC_F)utils/ $(SRC_F)parsing/
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LFLAGS) $(CFLAGS) -o $@ $(OBJ)

$(OBJ_F)%.o: %.c $(HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_F)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re bonus
