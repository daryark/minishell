GREEN = \033[0;32m
YELLOW = \033[0;33m
RE = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -Ireadline -L$(LFT_F) -lft -I$(LFT_F)
HEADERS = incl/minishell.h incl/execute.h incl/sources.h incl/parsing.h
LFT_F = libft
FT_DES = ft_destructor
FT_CLASS = ft_class

SRC =	minishell.c \
		execute.c builtins.c echo.c env.c \
		env_init.c parsing.c dollar_parse.c tokenize.c open_quotes.c cmd.c \
		utils_signals.c  utils_parsing.c utils_symbol.c path.c \
		err.c err_parsing.c env_lst.c arr.c split_save_divider.c clean.c \

SRC_F = src/
OBJ_F = obj/
VPATH = $(SRC_F) $(SRC_F)exec/ $(SRC_F)utils/ $(SRC_F)parsing/ 
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))

all: $(NAME)

.SILENT:
$(NAME): $(OBJ)
	@printf "\n"
	$(MAKE) -C $(FT_DES)
	$(MAKE) -C $(FT_CLASS)
	$(MAKE) -C $(LFT_F)
	$(CC) -o $@ $(OBJ) $(LFLAGS) $(CFLAGS) ./ft_destructor/ft_alloc.a ./ft_class/ft_class.a
	@echo "$(GREEN)\n—————————————✣ MINISHELL COMPILED ✣—————————————\n$(RE)"

$(OBJ_F)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(GREEN). $(RE)"

clean:
	rm -rf $(OBJ_F)

fclean: clean
	rm -f $(NAME)
	if [ -d "$(LFT_F)" ]; then \
		$(MAKE) fclean -C $(LFT_F); \
	fi

re: fclean all
	$(MAKE) fclean -C $(LFT_F);
	$(MAKE) fclean -C $(FT_CLASS);
	$(MAKE) fclean -C $(FT_DES);
	$(MAKE) -j 12 all

.PHONY:	all clean fclean re bonus