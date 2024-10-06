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
	printf("TOKENS COUNTER : %d\n", tokens_count);
	tokens = (char **)malloc((tokens_count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	tokens = tokens_alloc(s, c, tokens);
	return (tokens);
}