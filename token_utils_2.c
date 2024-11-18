#include "minishell.h"


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

int	is_delimiter(char *token)
{
	if (token[0] == '>' || token[0] == '<' || token[0] == '|')
		return (1);
	return (0);
}
