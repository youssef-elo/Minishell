/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:52:58 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:52:59 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	solo_child(t_exec *prompt, char *path, char **env_c)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prompt->fd_in != 0)
	{
		dup2(prompt->fd_in, 0);
		close(prompt->fd_in);
	}
	if (prompt->fd_out != 1)
	{
		dup2(prompt->fd_out, 1);
		close(prompt->fd_out);
	}
	execve(path, prompt->args, env_c);
	solo_exec_fail(prompt, path);
}

void	solo_exec(t_exec *prompt, char *path, char **env_c)
{
	int		f;
	pid_t	pid;
	int		status;

	f = fork();
	if (f == 0)
		solo_child(prompt, path, env_c);
	else
	{
		signal_set_wait();
		pid = waitpid(f, &status, 0);
		if (prompt->fd_in != 0)
			close(prompt->fd_in);
		if (prompt->fd_out != 1)
			close(prompt->fd_out);
		if (WIFSIGNALED(status))
			ft_exit_status(WTERMSIG(status) + 128, SET);
		else
			ft_exit_status(WEXITSTATUS(status), SET);
		set_signals(0, 0);
	}
}

void	solo_not_found(t_exec *prompt)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(prompt->cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	if (prompt->fd_in != 0)
		close (prompt->fd_in);
	if (prompt->fd_out != 1)
		close(prompt->fd_out);
	ft_exit_status(127, SET);
}

void	fd_close(int fd_in, int fd_out)
{
	if (fd_in > 1)
		close(fd_in);
	if (fd_out > 1)
		close(fd_out);
}

int	solo_pre(t_exec *prompt)
{
	if (prompt->fd_in == -1 || prompt->fd_out == -1)
	{
		fd_close(prompt->fd_in, prompt->fd_out);
		return (1);
	}
	if (!prompt->cmd)
	{
		if (prompt->fd_in)
			close(prompt->fd_in);
		if (prompt->fd_out != 1)
			close(prompt->fd_out);
		ft_exit_status(0, SET);
		return (1);
	}
	if (is_builtin(prompt))
	{
		if (prompt->fd_in != 0)
			close (prompt->fd_in);
		if (prompt->fd_out != 1)
			close(prompt->fd_out);
		return (1);
	}
	return (0);
}
