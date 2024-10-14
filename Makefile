NAME = minishell

FILES := $(shell ls *.c)
#remove forbiden

OFILES = $(FILES:.c=.o)

HEADER := $(shell ls *.h)
#also forbidden remove later

# SANITIZE = -g -fsanitize=address

FLAGS = -Wall -Wextra -Werror $(SANITIZE)

READLINE = -l readline

all : $(NAME)

$(NAME) : $(OFILES) $(HEADER)
	cc $(FLAGS) $(OFILES) $(READLINE) -o $(NAME)

%.o : %.c $(HEADER) Makefile
	cc -c $(FLAGS) $< -o $@

re : fclean all

clean :
	rm -rf $(OFILES)

fclean : clean
	rm -rf $(NAME)   