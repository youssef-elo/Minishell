#include "minishell.h"

int	tokens_counter(const char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == SEPARATOR)
			count++;
		i++;
	}
	return (count);
}

char	**ft_free(char **words, int j)
{
	while (j)
	{
		free(words[j - 1]);
		j--;
	}
	free(words);
	return (NULL);
}

t_token_type	delimiter_definer(char	*token)
{
	if (token[0] == '>')
	{
		if (token[1] == '>')
			return (OUTPUT_A);
		else
			return (OUTPUT_R);
	}
	else if (token[0] == '<')
	{
		if (token[1] == '<')
			return (HEREDOC);
		else
			return (INPUT_R);
	}
	else if (token[0] == '|')
		return (PIPE);
	return (PIPE);
}

t_token	*list_tokens_u(char **tok, t_token_type t_type, t_token *f_token, int c)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (is_delimiter(tok[i]))
			t_type = delimiter_definer(tok[i]);
		else if (i > 0 && is_delimiter(tok[i - 1])
			&& PIPE != delimiter_definer(tok[i - 1]))
			t_type = RDR_ARG;
		else
		{
			if (c == 0)
				t_type = CMD;
			else
				t_type = ARG;
			c++;
		}
		append_token(&f_token, tok[i], t_type);
		if (t_type == PIPE)
			c = 0;
		i++;
	}
	return (f_token);
}

t_token	*list_tokens(char **tokens)
{
	int				i;
	int				count;
	t_token			*first_token;
	t_token_type	token_type;

	i = 0;
	count = 0;
	token_type = NIL;
	first_token = NULL;
	return (list_tokens_u(tokens, token_type, first_token, count));
}
