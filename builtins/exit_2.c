/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:53:13 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:53:14 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	exit_atoi(char *str, int *check)
{
	int					i;
	int					s;
	unsigned long long	r;

	i = 0;
	r = 0;
	s = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s *= -1;
	}
	while (ft_is_digit(str[i]))
	{
		r = r * 10 + (str[i] - 48);
		if ((r > (t_ull)LLONG_MAX + 1) || (r > LLONG_MAX && s == 1))
		{
			*check = -1;
			return (255);
		}
		i++;
	}
	return ((long long)r * s);
}

int	ft_exit(t_exec *prompt, int pipe)
{
	int	check;
	int	exit_status;

	check = prompt->fd_in;
	if (isatty(STDIN_FILENO) && (pipe || !pipe))
		ft_putstr_fd("exit\n", 1);
	if (!prompt->args[1])
		return (my_exit(ft_exit_status(0, GET)));
	check = ft_exit_check(prompt->args[1]);
	if (check == 1)
		my_exit(exit_err(prompt->args[1]));
	if (check == 0 && !prompt->args[2])
	{
		exit_status = exit_atoi(prompt->args[1], &check);
		if (check == -1)
			my_exit(exit_err(prompt->args[1]));
		return (my_exit(exit_status % 256));
	}
	if (prompt->args[2])
	{
		ft_putstr_fd("minishell: exit : too many arguments\n", 2);
		return (1);
	}
	return (1);
}
