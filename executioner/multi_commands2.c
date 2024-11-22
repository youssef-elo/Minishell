#include "minishell.h"

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

// void	multi_exec(t_exec *prompt)
// {
// 	char		*path;
// 	char		*env_path;

// 	if (prompt->fd_in == -1 || prompt->fd_out == -1)
// 		my_exit (1);
// 	if (!prompt->cmd)
// 		my_exit(0);
// 	is_builtin_pipe(prompt);
// 	if ((prompt->cmd[0] == '.' && prompt->cmd[1] == '/')
// 		|| prompt->cmd[0] == '/')
// 	{
// 		execve(prompt->cmd, prompt->args, char_env(prompt->env));
// 		multi_exec_fail(prompt);
// 	}
// 	else
// 	{
// 		env_path = ft_getenv(prompt->env, "PATH");
// 		path = get_path(prompt->cmd, env_path);
// 		if (!env_path || !env_path[0])
// 			path = ft_strjoin("./", prompt->cmd);
// 		if (path)
// 			multi_exec_path(prompt, path);
// 	}
// 	put_multi("minishell: ", prompt->cmd, " : command not found\n", 2);
// 	my_exit(127);
// }

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
