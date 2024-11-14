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

// if (!ft_strncmp("_", env->key, 2))
// {
// 	env = env->next;
// 	continue ;
// }