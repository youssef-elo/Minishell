#include "minishell.h"

int	tokens_counter(const char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if(!cmd)
		return (1);
	while (cmd[i])
	{
		if(cmd[i] == SEPARATOR)
			count++;
		i++;	
	}
	return (count);
}

static	char	**ft_free(char **words, int j)
{
	while (j)
	{
		free(words[j - 1]);
		j--;
	}
	free(words);
	return (NULL);
}

char	**tokens_alloc(const char *s, char c, char **tokens)
{
	int	j;
	int	i;
	int	len;

	j = 0;
	i = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] != c)
		{
			len++;
			i++;
		}
		tokens[j] = ft_substr(s, (i - len), len);
		if (tokens[j] == NULL)
			return (ft_free(tokens, j));
		// printf("TOKEN N.%d : {%s}\n", j + 1, tokens[j]);
		if (s[i])
			i++;
		j++;
	}
	tokens[j] = NULL;
	return (tokens);
}

char	**split_tokens(const char *s, char c)
{
	int		tokens_count;
	char	**tokens;

	if (s == NULL)
		return (NULL);
	tokens_count = tokens_counter(s);
	tokens = (char **)gc_handler(((tokens_count + 1) * sizeof(char *)), MALLOC);
	if (tokens == NULL)
		return (NULL);
	tokens = tokens_alloc(s, c, tokens);
	return (tokens);
}

t_token_type	delimiter_definer(char	*token)
{
	if (token[0] == '>')
		if(token[1] == '>')
			return (OUTPUT_A);
		else
			return (OUTPUT_R);
	else if (token[0] == '<')
		if(token[1] == '<')
			return (HEREDOC);
		else
			return (INPUT_R);
	else if (token[0] == '|')
		return (PIPE);
	return (PIPE);
}

int	is_delimiter(char	*token)
{
	if(token[0] == '>' || token[0] == '<' || token[0] == '|')
		return (1);
	return (0);
}


t_token	*list_tokens(char **tokens)
{
	int				i;
	int				count;
	t_token			*first_token;
	t_token_type	token_type;

	count = 0;
	i = 0;
	first_token = NULL;
	token_type = NIL;
	while (tokens[i])
	{
		if(is_delimiter(tokens[i]))
			token_type = delimiter_definer(tokens[i]);
		else if(i > 0 && is_delimiter(tokens[i - 1]) && PIPE != delimiter_definer(tokens[i - 1]))
			token_type = RDR_ARG;
		else
		{
			if(count == 0)
				token_type = CMD;
			else
				token_type = ARG;
			count++;
		}
		append_token(&first_token, tokens[i], token_type);
		if (token_type == PIPE)
			count = 0;
		i++;
	}
	return (first_token);
}
