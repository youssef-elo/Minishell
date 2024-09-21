NAME = minishell

FILES := $(shell ls *.c)
#remove forbiden

OFILES = $(FILES:.c=.o)

HEADER = minishell.h header_hamza.h header_ysf.h

FLAGS = -Wall -Wextra -Werror 

READLINE = -l readline

all : $(NAME)

$(NAME) : $(OFILES) $(HEADER) 
	cc $(FLAGS) $(OFILES) $(READLINE) -o $(NAME)

%.o : %.c $(HEADER)
	cc -c $(FLAGS) $< -o $@

re : fclean all

clean :
	rm -rf $(OFILES)

fclean : clean
	rm -rf $(NAME)