/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:53:20 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:53:21 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_err(char *str)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (-1);
}

int	var_check(char *str)
{
	int	i;

	i = 1;
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (export_err(str));
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				return (0);
			else
				return (export_err(str));
		}
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| str[i] == '_' || (str[i] >= '0' && str[i] <= '9')))
			return (export_err(str));
		i++;
	}
	return (0);
}

char	*find_operator(char *str, int *set_append)
{
	int	i;

	i = 0;
	while (str[i])
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
			}
			f = 1;
		}
		tmp = tmp->next;
	}
	if (f == 0)
		export_append(exp, exp_node(key, value));
}
