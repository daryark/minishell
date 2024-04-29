NAME = minishell

CFLAGS = -Wall -Wextra -Werror 
LFLAGS = -lreadline
CC = cc
HEADERS = incl/minishell.h incl/execute.h incl/sources.h

#!struct of adding src files to src, just not to mess up for the eyes
#src folder files (minishell and maybe main)
#exec folder files
# parsing fodler files
# utils folder files
#! can delete after reading
SRC =	minishell.c \
		execute.c \
		parsing.c \
		source1.c

SRC_F = src/
OBJ_F = obj/
VPATH = $(SRC_F) $(SRC_F)exec/ $(SRC_F)utils/ $(SRC_F)parsing/
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LFLAGS) $(CFLAGS) -o $@ $(OBJ)

#! delete after you read it (can leave this comment at the end of file, if need)
# mkdir -p $(@D) - -p flag says to create the dir, if it doesn't exist. $(@D) takes the name from $(OBF_F) = obj/
# $@ (takes each obj file), $< takes first prerequisite for this rule (each .c file) - but not .h ro Makefile
# each .o need .c before, check changes in .h files used and in Makefile (for macros and function declarations changed mostly)
#!
$(OBJ_F)%.o: %.c $(HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ_F)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re bonus
