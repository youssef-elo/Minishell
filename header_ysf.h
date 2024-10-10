#ifndef HEADER_YSF_H
# define HEADER_YSF_H

#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "header_hamza.h"
#include <limits.h>

void ft_putstr_fd(char *str, int fd);

typedef struct s_execution
{
	char				*cmd;
	char				**args;
	int					fd_in;
	int					fd_out;
	struct s_execution	*next;
}						t_execution;

#endif