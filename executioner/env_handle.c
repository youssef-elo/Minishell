/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:52:36 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:52:37 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	equal_sign_position(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	alnm(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	shlvl_pwd_env(t_env **head, int sp[], char *pwd)
{
	if (!sp[0])
		append_node_env(head, "SHLVL", "1");
	if (!sp[1])
		append_node_env(head, "PWD", pwd);
}

long long	shlvl_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (ft_is_digit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		if (res > LLONG_MAX && sign == 1)
			return (2147463648);
		else if (res > (unsigned long long)LLONG_MAX + 1)
			return (2147463648);
		i++;
	}
	return ((long long)res * sign);
}

void	shlvl_update(t_env *tmp)
{
	long long	next;

	next = shlvl_atoi(tmp->value) + 1;
	if (tmp->value[0] == '-' && alnm(tmp->value + 1))
		tmp->value = ft_strdup_env("0");
	if (!alnm(tmp->value))
		tmp->value = ft_strdup_env("1");
	if ((*(tmp->value) == '+' && alnm(tmp->value + 1)) || alnm(tmp->value))
	{
		if (ft_strlen(tmp->value) > 12 || next > 2147483647)
			tmp->value = ft_strdup_env("0");
		else if (next - 1 >= 1000)
		{
			ft_putstr_fd("minishell: warning: shell level (", 2);
			ft_putstr_fd(ft_itoa(next), 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
			tmp->value = ft_strdup_env("1");
		}
		else if (next > 1000)
			tmp->value = ft_strdup_env("1");
		else if (next < 1000)
			tmp->value = ft_strdup_env(ft_itoa((int)next));
		else if (next == 1000)
			tmp->value = ft_strdup_env("");
	}
}
