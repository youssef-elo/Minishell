/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:52:47 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:52:48 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_status(int status, int action)
{
	static int	exit_status;

	if (action == SET)
	{
		exit_status = status;
		return (status);
	}
	return (exit_status);
}
