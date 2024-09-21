#ifndef HEADER_YSF_H
# define HEADER_YSF_H

#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "header_hamza.h"

void get_line(t_env *env);

enum token
{
	CMD,
	ARG,
	PIPE,
	INPUT_R,
	OUTPUT_R,
	OUTPUT_A,
	HEREDOC,
};

typedef struct s_token{
	enum token		type;
	char			*string;
	struct s_token	*next;
}				t_token;

#endif