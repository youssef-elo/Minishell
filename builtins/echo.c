/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:53:07 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:53:08 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_check(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j++] != '-' || !args[i][j])
			return (i);
		else
		{
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (i);
				j++;
			}
		}
		i++;
	}
	if (i == 1)
		return (i);
	return (-1);
}

int	ft_echo(t_exec *prompt)
{
	int	start;
	int	nl;

	start = flag_check(prompt->args);
	nl = start;
	if (start == -1)
		return (0);
	while (prompt->args[start])
	{
		ft_putstr_fd(prompt->args[start], prompt->fd_out);
		if (prompt->args[start + 1])
			write(prompt->fd_out, " ", 1);
		start++;
	}
	if (nl == 1)
		write(prompt->fd_out, "\n", 1);
	return (0);
}
