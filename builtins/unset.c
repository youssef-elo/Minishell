#include "../minishell.h"

int	unset_err(int *check, char *str)
{
	(*check)++;
	ft_putstr_fd("unset : '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (-1);
}

int	unset_check_var(char *str, int *check)
{
	int	i;

	i = 1;
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] <= 'Z' && str[0] >= 'A') || str[0] == '_'))
		return (unset_err(check, str));
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] <= 'Z' && str[i] >= 'A')
				|| str[i] == '_' || (str[i] >= '0' && str[i] <= '9')))
			return (unset_err(check, str));
		i++;
	}
	return (0);
}

void	unset_exp(t_export **head, char *str)
{
	t_export	*tmp;
	t_export	*pre;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->key, ft_strlen(tmp->key) + 1))
		{
			if (tmp == *head)
				*head = (*head)->next;
			else
				pre->next = tmp->next;
			return ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
}

void	unset_env(t_env **head, char *str)
{
	t_env	*tmp;
	t_env	*pre;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->key, ft_strlen(tmp->key) + 1))
		{
			if (tmp == *head)
				*head = (*head)->next;
			else
				pre->next = tmp->next;
			return ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_exec *prompt, t_export **head)
{
	int			i;
	int			check;

	i = 0;
	check = 0;
	while (prompt->args[i])
	{
		// printf("|%s|\n", prompt->args[i]);
		if (!unset_check_var(prompt->args[i], &check))
		{
			unset_exp(head, prompt->args[i]);
			unset_env(prompt->head, prompt->args[i]);
		}
		i++;
	}
	if (check)
		return (1);
	return (0);
}
