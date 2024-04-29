NAME = minishell

SRC = minishell.c

LFLAGS = -lreadline

OBJ = $(SRC:.c=.o) $(UTILS_LIB:.c=.o)

CC = cc

UTILS_LIB = utils/*.c
SRC_LIB = src/*.c

CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LFLAGS) $(CFLAGS) -o $(NAME) $(SRC) $(UTILS_LIB) $(SRC_LIB)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re bonus