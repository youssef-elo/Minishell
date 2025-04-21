/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:52:53 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:52:54 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multi_exec_path(t_exec *pr, char *path)
{
	struct stat	path_info;

	execve(path, pr->args, char_env(pr->env));
	if (!stat(path, &path_info))
	{
		if (S_ISDIR(path_info.st_mode))
		{
			put_multi("minishell: ", pr->cmd, ": is a directory\n", 2);
			my_exit(126);
		}
		else
		{
			put_multi("minishell: ", pr->cmd, " Permission denied\n", 2);
			my_exit(126);
		}
	}
	else
	{
		put_multi("minishell: ", pr->cmd, ": No such file or directory\n", 2);
		my_exit(127);
	}
}

void	fork_fail_cleanup(t_exec *prompt, int pre_pipe)
{
	if (pre_pipe != -1)
		close(pre_pipe);
	while (prompt)
	{
		if (prompt->fd_in != 0)
			close(prompt->fd_in);
		if (prompt->fd_out != 1)
			close(prompt->fd_out);
		prompt = prompt->next;
	}
}

int	fork_fail(t_exec *prompt, int *pip, int pre_id)
{
	perror("minishell: fork ");
	close(pip[0]);
	close(pip[1]);
	if (prompt->fd_in != 0)
		close(prompt->fd_in);
	if (prompt->fd_out != 1)
		close(prompt->fd_out);
	ft_wait(pre_id);
	ft_exit_status(1, SET);
	return (0);
}

void	ft_wait(int lastp)
{
	pid_t	wpid;
	int		stat;

	signal_set_wait();
	wpid = waitpid(-1, &stat, 0);
	while (wpid != -1)
	{
		if (wpid == lastp)
		{
			if (WIFSIGNALED(stat))
				ft_exit_status(WTERMSIG(stat) + 128, SET);
			else
				ft_exit_status(WEXITSTATUS(stat), SET);
		}
		wpid = waitpid(-1, &stat, 0);
	}
	set_signals(0, 0);
}

char	*get_path(char *cmd, char *path)
{
	int			i;
	char		*new_cmd;
	char		*cmd_path;
	char		**path_split;
	struct stat	path_info;

	i = 0;
	if (!path || !cmd || !(*cmd))
		return (NULL);
	new_cmd = ft_strjoin("/", cmd);
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		cmd_path = ft_strjoin(path_split[i], new_cmd);
		if (!stat(cmd_path, &path_info))
		{
			if (S_ISREG(path_info.st_mode))
				return (cmd_path);
		}
		i++;
	}
	return (NULL);
}
