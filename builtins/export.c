#include "../minishell.h"

void	put_export(t_exec *prompt, t_export *exp)
{
	while (exp)
	{
		ft_putstr_fd("declare -x ", prompt->fd_out);
		ft_putstr_fd(exp->key, prompt->fd_out);
		if (exp->value)
		{
			ft_putstr_fd("=\"", prompt->fd_out);
			ft_putstr_fd(exp->value, prompt->fd_out);
			ft_putstr_fd("\"", prompt->fd_out);
		}
		ft_putstr_fd("\n", prompt->fd_out);
		exp = exp->next;
	}
}

void	export_sort(t_export **head, t_export *node, t_export *tm, t_export *pr)
{
	while (tm)
	{
		if (ft_strncmp(tm->key, node->key, ft_strlen(node->key) + 1) > 0)
		{
			if (*head == tm)
			{
				node->next = *head;
				*head = node;
				return ;
			}
			else
			{
				node->next = tm;
				pr->next = node;
				return ;
			}
		}
		else if (!tm->next)
		{
			tm->next = node;
			return ;
		}
		pr = tm;
		tm = tm->next;
	}
}

void	export_append(t_export **head, t_export *node)
{
	int			key_l;
	t_export	*tmp;
	t_export	*pre;

	if (!(*head))
	{
		*head = node;
		return ;
	}
	tmp = *head;
	pre = tmp;
	export_sort(head, node, tmp, pre);
	key_l = ft_strlen(node->key) + 1;
}

void	export_init(t_env *env, t_export **exp)
{
	t_export	*node;

	while (env)
	{
		if (!ft_strncmp("_", env->key, 2))
		{
			env = env->next;
			continue ;
		}
		node = galloc(sizeof(t_export), MALLOC);
		node->next = NULL;
		node->key = env->key;
		node->value = env->value;
		export_append(exp, node);
		env = env->next;
	}
	node = galloc(sizeof(t_export), MALLOC);
	node->next = NULL;
	node->key = ft_strdup_env("OLDPWD");
	node->value = NULL;
	export_append(exp, node);
}

int	var_check(char *str)
{
	int i;

	i = 1;
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (-1);
	}
	while(str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				return (0);
			else
			{
				ft_putstr_fd("export: '", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (-1);
			}
		}
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' || (str[i] >= '0' && str[i] <='9')))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*find_operator(char *str, int *set_append)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
		{
			*set_append = 1;
			return (str + i + 1);
		}
		else if (str[i] == '+' && str[i + 1] == '=')
		{
			*set_append = 2;
			return (str + i + 2);
		}
		i++;
	}
	*set_append = 0;
	return (NULL);
}

t_export	*exp_node(char *key, char *value)
{
	t_export	*node;

	node = galloc(sizeof(t_export), MALLOC);
	node->next = NULL;
	node->key = ft_strdup_env(key);
	node->value = ft_strdup_env(value);
	return (node);
}

void	update_append_exp(t_export **exp, int set_apnd, char *key, char *value)
{
	int			f;
	t_export	*tmp;

	f = 0;
	tmp = *exp;
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1))
		{
			if (value)
			{
				if (set_apnd == 1)
					tmp->value = ft_strdup_env(value);
				else if (set_apnd == 2)
					tmp->value = ft_strjoin_env(tmp->value, value);
			}
			f = 1;
		}
		tmp = tmp->next;
	}
	if (f == 0)
		export_append(exp, exp_node(key, value));
}

void	update_append_env(t_env **env, int set_apnd, char *key, char *value)
{
	int		f;
	t_env	*tmp;

	f = 0;
	tmp = *env;
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1))
		{
			if (value)
			{
				if (set_apnd == 1)
					tmp->value = ft_strdup_env(value);
				else if (set_apnd == 2)
					tmp->value = ft_strjoin_env(tmp->value , value);
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
	int val_len;
	int key_len;

	key_len = 0;
	val_len = 0;
	while(str[key_len] && str[key_len] != '+' && str[key_len] != '=')
		key_len++;
	*key = gc_handler(key_len + 1, MALLOC);
	ft_strlcpy(*key, str, key_len + 1);
	if (str[key_len])
	{
		*value = ft_strdup(str + key_len + set_apnd);
	}
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
	while(prompt->args[i])
	{
		pos = find_operator(prompt->args[i], &apnd_set);
		if (var_check(prompt->args[i]) == -1)
		{
			(*check)++;
			i++;
			continue ;
		}
		ft_substr_exp(prompt->args[i], &key, &val, apnd_set);
		if (val)
			update_append_env(prompt->head, apnd_set, key, val);
		update_append_exp(head, apnd_set, key , val);
		i++;
	}
}

int	ft_export(t_exec *prompt, t_export **head)
{
	int	check;
	// static t_export	*head;
	// static int		f;

	// check = 0;
	// if (f == 0)
	// {
	// 	export_init(prompt->env, head);
	// 	f = 1;
	// }
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
