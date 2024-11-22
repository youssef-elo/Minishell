NAME = minishell

PARSING = parsing/parsing.c \
		parsing/split_str.c
		parsing/token_utils.c
		parsing/syntax_error.c
		parsing/string_utils.c
		parsing/string_utils2.c
		parsing/string_utils3.c
		parsing/token_utils_2.c
		parsing/heredoc_tools.c
		parsing/command_parser.c
		parsing/parsing_tools_1.c
		parsing/parsing_tools_2.c
		parsing/parsing_tools_3.c
		parsing/garbage_collector.c
		parsing/linked_list_utils.c
		parsing/command_formatter.c
		parsing/open_redirections.c
		parsing/dollar_sign_formatter.c

EXECUTIONER = executioner/signals.c\
			executioner/env_utils.c \
			executioner/execution.c  \
			executioner/is_builtin.c  \
			executioner/env_handle.c   \
			executioner/env_handle2.c   \
			executioner/exit_status.c    \
			executioner/solo_command.c    \
			executioner/multi_commands.c   \
			executioner/multi_commands2.c   \

UTILS = utils/ft_atoi.c \
		utils/ft_itoa.c  \
		utils/main_utils.c\
		utils/string_put.c \

BUILTINS =	builtins/cd.c \
			builtins/pwd.c \
			builtins/env.c  \
			builtins/echo.c  \
			builtins/exit.c	  \
			builtins/unset.c   \
			builtins/exit_2.c   \
			builtins/export.c    \
			builtins/export_2.c   \
			builtins/export_3.c    \

FILES := $(shell ls *.c builtins/*.c parsing/*.c)
#remove forbiden

OFILES = $(FILES:.c=.o)

HEADER := $(shell ls *.h)
#also forbidden remove later

SANITIZE = -g -fsanitize=address
# 
FLAGS = -Wall -Wextra -Werror $(SANITIZE)

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
