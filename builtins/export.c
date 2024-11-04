#include "../minishell.h"

void put_export(t_exec *prompt, t_export *exp)
{
	while(exp)
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


void print_list(t_export *head)
{
	while(head)
	{
		printf("%s\n", head->key);
		head = head->next;
	}
	puts("-----------------\n");
}

void export_append(t_export **head, t_export *node)
{
	int key_l;
	t_export *tmp;
	t_export *pre;

	if (!(*head))
	{
		*head = node;
		return;
	}
	tmp = *head;
	pre = tmp;
	key_l = ft_strlen(node->key) + 1;
	while(tmp)
	{
		if (ft_strncmp(tmp->key, node->key, key_l) > 0)
		{
			if (*head == tmp)
			{
				// printf("%s\n", tmp->key);
				node->next = *head;
				*head = node;
				return ;
			}
			else
			{
				// printf("other : %s\t to add : %s\n", tmp->key, node->key);
				// print_list(*head);
				node->next = tmp;
				pre->next = node;
				return ; 
			}
		}
		else if (!tmp->next)
		{
			tmp->next = node;
			return ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
}

void	export_init(t_env *env, t_export **exp)
{
	t_export *node;

	// last = NULL;
	while(env)	
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
		// printf("%s\n", node->key);
		// if (last)
		// {
		// 	while(last->next)
		// 		last = last->next;
		// 	last->next = node;
		// }
		// else
		// {
		// 	*exp = node;
		// 	last = node;
		// }
		export_append(exp, node);
		env = env->next;
	}
	node = galloc(sizeof(t_export), MALLOC);
	node->next = NULL;
	node->key = ft_strdup_env("OLDPWD");
	node->value = NULL;
	export_append(exp, node);
}

int ft_export(t_exec *prompt)
{
	static t_export *head;
	static int f;

	if (f == 0)
	{
		export_init(prompt->env, &head);
		f = 1;
	}
	if (!prompt->args[1])
	{
		put_export(prompt, head);
		return (0);
	}
	return (0);
}
