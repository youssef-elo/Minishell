NAME = minishell

FILES := $(shell ls *.c builtins/*.c)
#remove forbiden

OFILES = $(FILES:.c=.o)

HEADER := $(shell ls *.h)
#also forbidden remove later

# SANITIZE = -g -fsanitize=address

# FLAGS = -Wall -Wextra -Werror $(SANITIZE)

LIBS =  -L ~/.brew/opt/readline/lib -l readline

INCLUDES = -I ~/.brew/opt/readline/include

all : $(NAME)

n9i : all clean

$(NAME) : $(OFILES) $(HEADER)
	cc $(FLAGS) $(OFILES) $(LIBS) -o $(NAME)

%.o : %.c $(HEADER) Makefile
	cc -c $(FLAGS) $(INCLUDES) $< -o $@

re : fclean all

clean :
	rm -rf $(OFILES)

fclean : clean
	rm -rf $(NAME)
