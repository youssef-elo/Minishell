#include "../minishell.h"

void	update_append_env(t_env **env, int set_apnd, char *key, char *value)
{
	int		f;
	t_env	*tmp;

	f = 0;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1))
		{
			if (value)
			{
				if (set_apnd == 1)
					tmp->value = ft_strdup_env(value);
				else if (set_apnd == 2)
					tmp->value = ft_strjoin_env(tmp->value, value);
				f = 1;
			}
		}
		tmp = tmp->next;
	}
	if (f == 0)
		append_node_env(env, key, value);
}

void	ft_substr_exp(char *str, char **key, char **value, int set_apnd)
{
	int	val_len;
	int	key_len;

	key_len = 0;
	val_len = 0;
	while (str[key_len] && str[key_len] != '+' && str[key_len] != '=')
		key_len++;
	*key = gc_handler(key_len + 1, MALLOC);
	ft_strlcpy(*key, str, key_len + 1);
	if (str[key_len])
		*value = ft_strdup(str + key_len + set_apnd);
	else
		*value = NULL;
}

void	export_var(t_exec *prompt, t_export **head, int *check)
{
	int		i;
	char	*pos;
	char	*key;
	char	*val;
	int		apnd_set;

	i = 1;
	val = NULL;
	key = NULL;
	apnd_set = 0;
	while (prompt->args[i])
	{
		pos = find_operator(prompt->args[i], &apnd_set);
		if (var_check(prompt->args[i]) == -1)
		{
			(*check)++;
			i++;
			continue ;
		}
		ft_substr_exp(prompt->args[i], &key, &val, apnd_set);
		if (!ft_strncmp(key, "_", ft_strlen(key)))
		{
			i++;
			continue ;
		}
		if (val)
			update_append_env(prompt->head, apnd_set, key, val);
		update_append_exp(head, apnd_set, key, val);
		i++;
	}
}

int	ft_export(t_exec *prompt, t_export **head)
{
	int	check;

	check = 0;
	if (!prompt->args[1])
	{
		put_export(prompt, *head);
		return (0);
	}
	else
	{
		export_var(prompt, head, &check);
		if (check)
			return (1);
	}
	return (0);
}

int	export_unset_cd(t_exec *prompt, int sw)
{
	static t_export	*head;
	static int		f;

	if (f == 0)
	{
		export_init(prompt->env, &head);
		f = 1;
	}
	if (sw == 1)
		return (ft_export(prompt, &head));
	else if (sw == 2)
		return (ft_unset(prompt, &head));
	else
		return (ft_cd(prompt, &head));
}
