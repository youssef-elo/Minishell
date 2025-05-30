/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:53:01 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:53:02 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	solo_exec_fail(t_exec *pr, char *path)
{
	struct stat	path_info;

	if (!stat(path, &path_info))
	{
		if (S_ISDIR(path_info.st_mode))
		{
			put_multi("minishell: ", pr->cmd, ": is a directory\n", 2);
			ft_exit_status(126, SET);
		}
		else
		{
			put_multi("minishell: ", pr->cmd, " Permission denied\n", 2);
			ft_exit_status(126, SET);
		}
	}
	else
	{
		put_multi("minishell: ", pr->cmd, ": No such file or directory\n", 2);
		ft_exit_status(127, SET);
	}
	my_exit(ft_exit_status(0, GET));
}
