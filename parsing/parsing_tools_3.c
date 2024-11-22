#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

void	toggle(int *boolean)
{
	if (*boolean)
		*boolean = 0;
	else
		*boolean = 1;
}

int	is_expandable(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '"' || delimiter[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

char	*expand_token(char *cmd, t_env *env_list)
{
	int	i;
	int	cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd);
	if (!cmd)
		return (NULL);
	while (env_list)
	{
		if (ft_strncmp(cmd, env_list->key, cmd_len + 1) == 0)
		{
			if (!env_list->value[0])
				return (NULL);
			return (env_list->value);
		}
		env_list = env_list->next;
	}
	return (NULL);
}
