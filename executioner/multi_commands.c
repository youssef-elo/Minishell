#include "../minishell.h"

void	child_process(t_exec *prompt, int pre_pipe, int *pip)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pre_pipe != -1 && prompt->fd_in == 0)
	{
		dup2(pre_pipe, 0);
		close(pre_pipe);
	}
	else if (prompt->fd_in != 0)
		dup2(prompt->fd_in, 0);
	if (prompt->next && prompt->fd_out == 1)
		dup2(pip[1], 1);
	else if (prompt->fd_out != 1)
		dup2(prompt->fd_out, 1);
	close(pip[0]);
	multi_exec(prompt);
}

int	child_setup(t_exec *prompt, int *pip, int *c_pid)
{
	int	pre_id;

	if (prompt->next)
	{
		if (pipe(pip))
		{
			perror("pipe ");
			close(pip[0]);
			close(pip[1]);
			if (prompt->fd_in != 0)
				close(prompt->fd_in);
			if (prompt->fd_out != 1)
				close(prompt->fd_out);
			return (0);
		}
	}
	pre_id = *c_pid;
	*c_pid = fork();
	if (*c_pid == -1)
		return (fork_fail(prompt, pip, pre_id));
	return (1);
}

void	parent_process(t_exec *prompt, int *pre_pipe, int *pip)
{
	if (*pre_pipe != -1)
		close(*pre_pipe);
	*pre_pipe = dup(pip[0]);
	close(pip[0]);
	close(pip[1]);
	if (prompt->fd_in != 0)
		close (prompt->fd_in);
	if (prompt->fd_out != 1)
		close(prompt->fd_out);
}

void	multi_exec_fail(t_exec *pr)
{
	struct stat	path_info;

	if (!stat(pr->cmd, &path_info))
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

void	multi_exec(t_exec *prompt)
{
	char		*path;
	char		*env_path;

	if (prompt->fd_in == -1 || prompt->fd_out == -1)
		my_exit (1);
	if (!prompt->cmd)
		my_exit(0);
	is_builtin_pipe(prompt);
	if ((prompt->cmd[0] == '.' && prompt->cmd[1] == '/')
		|| prompt->cmd[0] == '/')
	{
		execve(prompt->cmd, prompt->args, char_env(prompt->env));
		multi_exec_fail(prompt);
	}
	else
	{
		env_path = ft_getenv(prompt->env, "PATH");
		path = get_path(prompt->cmd, env_path);
		if (!env_path || !env_path[0])
			path = ft_strjoin("./", prompt->cmd);
		if (path)
			multi_exec_path(prompt, path);
	}
	put_multi("minishell: ", prompt->cmd, " : command not found\n", 2);
	my_exit(127);
}
