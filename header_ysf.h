#ifndef HEADER_YSF_H
# define HEADER_YSF_H

#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "header_hamza.h"

typedef struct s_execution
{
	char				*cmd;
	char				**args;
	int					fd_in;
	int					fd_out;
	struct s_execution	*next;
}						t_execution;

#endif