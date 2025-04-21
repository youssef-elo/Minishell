/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:53:15 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:53:16 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_check(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_is_digit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	my_exit(int exit_status)
{
	galloc(0, FREE);
	gc_handler(0, FREE);
	exit(exit_status);
	return (exit_status);
}

void	readline_exit(void)
{
	write(1, "exit\n", 5);
	galloc(0, FREE);
	gc_handler(0, FREE);
	exit(ft_exit_status(0, GET));
}

int	exit_err(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}
