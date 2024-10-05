#include "minishell.h"

int	tokens_counter(const char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if(!cmd)
		return (1);
	if(cmd)
		count++;
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
		while (s[i] != '\0' && s[i] != c)
		{
			len++;
			i++;
		}
		// printf("%d~\n", i);
		tokens[j] = ft_substr(s, (i - len), len);
		if (tokens[j] == NULL)
			return (ft_free(tokens, j));
		if (s[i])
			i++;
		j++;
	}
	// printf("5\n");
	return (tokens);
}

char	**split_tokens(const char *s, char c)
{
	int		tokens_count;
	char	**tokens;

	if (s == NULL)
		return (NULL);
	tokens_count = tokens_counter(s);
	tokens = (char **)malloc((tokens_count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	tokens[tokens_count] = NULL;
	tokens = tokens_alloc(s, c, tokens);
	// printf("SSS\n");
	return (tokens);
}