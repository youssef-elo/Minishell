NAME = minishell

FILES = reading_line.c string_utils.c linked_list_utils.c minishell.c

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