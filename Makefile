NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LFLAGS = -lreadline -Ireadline -L$(LFT_F) -lft -I$(LFT_F)
HEADERS = incl/minishell.h incl/execute.h incl/sources.h
LFT_F = libft
LFT_GIT = https://github.com/daryark/libft.git

SRC =	minishell.c \
		execute.c \
		parsing.c init_env.c parse_err.c utils_parsing.c dollar_parse.c \
		struct.c \
		utils.c \

SRC_F = src/
OBJ_F = obj/
VPATH = $(SRC_F) $(SRC_F)exec/ $(SRC_F)utils/ $(SRC_F)parsing/
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))

all: $(LFT_F) $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LFT_F)
	$(CC) -o $@ $(OBJ) $(LFLAGS) $(CFLAGS)

$(OBJ_F)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LFT_F):
	git clone $(LFT_GIT) $(LFT)

clean:
	rm -rf $(OBJ_F)

fclean: clean
	rm -f $(NAME)
	if [ -d "$(LFT_F)" ]; then \
		$(MAKE) fclean -C $(LFT_F); \
	fi
re: fclean all

.PHONY:	all clean fclean re bonus