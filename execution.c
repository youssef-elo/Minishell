#include "minishell.h"

// int	is_builtin(t_exec *prompt)
// {
// 	int	len;

// 	len = ft_strlen(prompt->cmd) + 1;
// 	if (!ft_strncmp(prompt->cmd, "echo", len))
// 		ft_exit_status(ft_echo(prompt), SET);
// 	else if (!ft_strncmp(prompt->cmd, "pwd", len))
// 		ft_exit_status(ft_pwd(prompt), SET);
// 	else if (!ft_strncmp(prompt->cmd, "exit", len))
// 		ft_exit_status(ft_exit(prompt, 0), SET);
// 	else if (!ft_strncmp(prompt->cmd, "cd", len))
// 		ft_exit_status(export_unset_cd(prompt, 3), SET);
// 	else if (!ft_strncmp(prompt->cmd, "env", len)
// 		&& ft_getenv(prompt->env, "PATH"))
// 		ft_exit_status(ft_env(prompt), SET);
// 	else if (!ft_strncmp(prompt->cmd, "unset", len))
// 		ft_exit_status(export_unset_cd(prompt, 2), SET);
// 	else if (!ft_strncmp(prompt->cmd, "export", len))
// 		ft_exit_status(export_unset_cd(prompt, 1), SET);
// 	else
// 		return (0);
// 	return (1);
// }

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

// void	solo_exec_fail(t_exec *pr, char *path)
// {
// 	struct stat	path_info;

// 	if (!stat(path, &path_info))
// 	{
// 		if (S_ISDIR(path_info.st_mode))
// 		{
// 			put_multi("minishell: ", pr->cmd, ": is a directory\n", 2);
// 			ft_exit_status(126, SET);
// 		}
// 		else
// 		{
// 			put_multi("minishell: ", pr->cmd, " Permission denied\n", 2);
// 			ft_exit_status(126, SET);
// 		}
// 	}
// 	else
// 	{
// 		put_multi("minishell: ", pr->cmd, ": No such file or directory\n", 2);
// 		ft_exit_status(127, SET);
// 	}
// 	my_exit(ft_exit_status(0, GET));
// }

// void	solo_child(t_exec *prompt, char *path, char **env_c)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	if (prompt->fd_in != 0)
// 	{
// 		dup2(prompt->fd_in, 0);
// 		close(prompt->fd_in);
// 	}
// 	if (prompt->fd_out != 1)
// 	{
// 		dup2(prompt->fd_out, 1);
// 		close(prompt->fd_out);
// 	}
// 	execve(path, prompt->args, env_c);
// 	solo_exec_fail(prompt, path);
// }

// void	solo_exec(t_exec *prompt, char *path, char **env_c)
// {
// 	int		f;
// 	pid_t	pid;
// 	int		status;

// 	f = fork();
// 	if (f == 0)
// 		solo_child(prompt, path, env_c);
// 	else
// 	{
// 		signal_set_wait();
// 		pid = waitpid(f, &status, 0);
// 		if (prompt->fd_in != 0)
// 			close(prompt->fd_in);
// 		if (prompt->fd_out != 1)
// 			close(prompt->fd_out);
// 		if (WIFSIGNALED(status))
// 			ft_exit_status(WTERMSIG(status) + 128, SET);
// 		else
// 			ft_exit_status(WEXITSTATUS(status), SET);
// 		set_signals(0, 0);
// 	}
// }

// void	solo_not_found(t_exec *prompt)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	ft_putstr_fd(prompt->cmd, 2);
// 	ft_putstr_fd(" : command not found\n", 2);
// 	if (prompt->fd_in != 0)
// 		close (prompt->fd_in);
// 	if (prompt->fd_out != 1)
// 		close(prompt->fd_out);
// 	ft_exit_status(127, SET);
// }

// int	solo_pre(t_exec *prompt)
// {
// 	if (prompt->fd_in == -1 || prompt->fd_out == -1)
// 		return (1);
// 	if (!prompt->cmd)
// 	{
// 		if (prompt->fd_in)
// 			close(prompt->fd_in);
// 		if (prompt->fd_out != 1)
// 			close(prompt->fd_out);
// 		ft_exit_status(0, SET);
// 		return (1);
// 	}
// 	if (is_builtin(prompt))
// 	{
// 		if (prompt->fd_in != 0)
// 			close (prompt->fd_in);
// 		if (prompt->fd_out != 1)
// 			close(prompt->fd_out);
// 		return (1);
// 	}
// 	return (0);
// }

// void	solo_command(t_exec *prompt, char **env_c)
// {
// 	char	*path;
// 	char	*env_path;

// 	if (solo_pre(prompt))
// 		return ;
// 	if ((prompt->cmd[0] == '.' && prompt->cmd[1] == '/')
// 		|| prompt->cmd[0] == '/')
// 		return (solo_exec(prompt, prompt->cmd, env_c));
// 	else
// 	{
// 		env_path = ft_getenv(prompt->env, "PATH");
// 		path = get_path(prompt->cmd, env_path);
// 		if (!env_path || !env_path[0])
// 		{
// 			path = ft_strjoin("./", prompt->cmd);
// 			solo_exec(prompt, path, env_c);
// 			return ;
// 		}
// 		if (path)
// 		{
// 			solo_exec(prompt, path, env_c);
// 			return ;
// 		}
// 	}
// 	solo_not_found(prompt);
// }

// void	is_builtin_pipe(t_exec *prompt)
// {
// 	int		len;

// 	len = ft_strlen(prompt->cmd) + 1;
// 	if (!ft_strncmp(prompt->cmd, "echo", len))
// 		exit(ft_echo(prompt));
// 	else if (!ft_strncmp(prompt->cmd, "pwd", len))
// 		exit(ft_pwd(prompt));
// 	else if (!ft_strncmp(prompt->cmd, "exit", len))
// 		exit(ft_exit(prompt, 1));
// 	else if (!ft_strncmp(prompt->cmd, "cd", len))
// 		exit(export_unset_cd(prompt, 3));
// 	else if (!ft_strncmp(prompt->cmd, "env", len)
// 		&& ft_getenv(prompt->env, "PATH"))
// 		exit(ft_env(prompt));
// 	else if (!ft_strncmp(prompt->cmd, "unset", len))
// 		exit(export_unset_cd(prompt, 2));
// 	else if (!ft_strncmp(prompt->cmd, "export", len))
// 		exit(export_unset_cd(prompt, 1));
// }

// void	multi_exec_fail(t_exec *pr)
// {
// 	struct stat	path_info;

// 	if (!stat(pr->cmd, &path_info))
// 	{
// 		if (S_ISDIR(path_info.st_mode))
// 		{
// 			put_multi("minishell: ", pr->cmd, ": is a directory\n", 2);
// 			my_exit(126);
// 		}
// 		else
// 		{
// 			put_multi("minishell: ", pr->cmd, " Permission denied\n", 2);
// 			my_exit(126);
// 		}
// 	}
// 	else
// 	{
// 		put_multi("minishell: ", pr->cmd, ": No such file or directory\n", 2);
// 		my_exit(127);
// 	}
// }

// void	multi_exec_path(t_exec *pr, char *path)
// {
// 	struct stat	path_info;

// 	execve(path, pr->args, char_env(pr->env));
// 	if (!stat(path, &path_info))
// 	{
// 		if (S_ISDIR(path_info.st_mode))
// 		{
// 			put_multi("minishell: ", pr->cmd, ": is a directory\n", 2);
// 			my_exit(126);
// 		}
// 		else
// 		{
// 			put_multi("minishell: ", pr->cmd, " Permission denied\n", 2);
// 			my_exit(126);
// 		}
// 	}
// 	else
// 	{
// 		put_multi("minishell: ", pr->cmd, ": No such file or directory\n", 2);
// 		my_exit(127);
// 	}
// }

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

// void	ft_wait(int lastp)
// {
// 	pid_t	wpid;
// 	int		stat;

// 	signal_set_wait();
// 	wpid = waitpid(-1, &stat, 0);
// 	while (wpid != -1)
// 	{
// 		if (wpid == lastp)
// 		{
// 			if (WIFSIGNALED(stat))
// 				ft_exit_status(WTERMSIG(stat) + 128, SET);
// 			else
// 				ft_exit_status(WEXITSTATUS(stat), SET);
// 		}
// 		wpid = waitpid(-1, &stat, 0);
// 	}
// 	set_signals(0, 0);
// }

// void	child_process(t_exec *prompt, int pre_pipe, int *pip)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	if (pre_pipe != -1 && prompt->fd_in == 0)
// 	{
// 		dup2(pre_pipe, 0);
// 		close(pre_pipe);
// 	}
// 	else if (prompt->fd_in != 0)
// 		dup2(prompt->fd_in, 0);
// 	if (prompt->next && prompt->fd_out == 1)
// 		dup2(pip[1], 1);
// 	else if (prompt->fd_out != 1)
// 		dup2(prompt->fd_out, 1);
// 	close(pip[0]);
// 	multi_exec(prompt);
// }

// int	fork_fail(t_exec *prompt, int *pip, int pre_id)
// {
// 	perror("minishell: fork ");
// 	close(pip[0]);
// 	close(pip[1]);
// 	if (prompt->fd_in != 0)
// 		close(prompt->fd_in);
// 	if (prompt->fd_out != 1)
// 		close(prompt->fd_out);
// 	ft_wait(pre_id);
// 	ft_exit_status(1, SET);
// 	return (0);
// }

// int	child_setup(t_exec *prompt, int *pip, int *c_pid)
// {
// 	int	pre_id;

// 	if (prompt->next)
// 	{
// 		if (pipe(pip))
// 		{
// 			perror("pipe ");
// 			close(pip[0]);
// 			close(pip[1]);
// 			if (prompt->fd_in != 0)
// 				close(prompt->fd_in);
// 			if (prompt->fd_out != 1)
// 				close(prompt->fd_out);
// 			return (0);
// 		}
// 	}
// 	pre_id = *c_pid;
// 	*c_pid = fork();
// 	if (*c_pid == -1)
// 		return (fork_fail(prompt, pip, pre_id));
// 	return (1);
// }

// void	parent_process(t_exec *prompt, int *pre_pipe, int *pip)
// {
// 	if (*pre_pipe != -1)
// 		close(*pre_pipe);
// 	*pre_pipe = dup(pip[0]);
// 	close(pip[0]);
// 	close(pip[1]);
// 	if (prompt->fd_in != 0)
// 		close (prompt->fd_in);
// 	if (prompt->fd_out != 1)
// 		close(prompt->fd_out);
// }

// void	fork_fail_cleanup(t_exec *prompt, int pre_pipe)
// {
// 	if (pre_pipe != -1)
// 		close(pre_pipe);
// 	while (prompt)
// 	{
// 		if (prompt->fd_in != 0)
// 			close(prompt->fd_in);
// 		if (prompt->fd_out != 1)
// 			close(prompt->fd_out);
// 		prompt = prompt->next;
// 	}
// }

// void	multi_commands(t_exec *prompt)
// {
// 	int	c_pid;
// 	int	lastp;
// 	int	pip[2];
// 	int	pre_pipe;

// 	pre_pipe = -1;
// 	while (prompt)
// 	{
// 		if (!child_setup(prompt, pip, &c_pid))
// 			return (fork_fail_cleanup(prompt, pre_pipe));
// 		if (c_pid == 0)
// 			child_process(prompt, pre_pipe, pip);
// 		else
// 		{
// 			parent_process(prompt, &pre_pipe, pip);
// 			if (!prompt->next)
// 				lastp = c_pid;
// 		}
// 		prompt = prompt->next;
// 	}
// 	ft_wait(lastp);
// }

void	multi_commands(t_exec *prompt)
{
	int	c_pid;
	int	lastp;
	int	pip[2];
	int	pre_pipe;

	pre_pipe = -1;
	while (prompt)
	{
		if (!child_setup(prompt, pip, &c_pid))
			return (fork_fail_cleanup(prompt, pre_pipe));
		if (c_pid == 0)
			child_process(prompt, pre_pipe, pip);
		else
		{
			parent_process(prompt, &pre_pipe, pip);
			if (!prompt->next)
				lastp = c_pid;
		}
		prompt = prompt->next;
	}
	ft_wait(lastp);
}

void	solo_command(t_exec *prompt, char **env_c)
{
	char	*path;
	char	*env_path;

	if (solo_pre(prompt))
		return ;
	if ((prompt->cmd[0] == '.' && prompt->cmd[1] == '/')
		|| prompt->cmd[0] == '/')
		return (solo_exec(prompt, prompt->cmd, env_c));
	else
	{
		env_path = ft_getenv(prompt->env, "PATH");
		path = get_path(prompt->cmd, env_path);
		if (!env_path || !env_path[0])
		{
			path = ft_strjoin("./", prompt->cmd);
			solo_exec(prompt, path, env_c);
			return ;
		}
		if (path)
		{
			solo_exec(prompt, path, env_c);
			return ;
		}
	}
	solo_not_found(prompt);
}
//in solo commands when entering variablethat doesnt exit execution gets null no struct , but in pipes i do get an empty string
void	main_exec(t_exec *prompt)
{
	// printf("%p\n", prompt);
	if (!prompt)
		return ;
	if (!prompt->next)
		solo_command(prompt, char_env(prompt->env));
	else
		multi_commands(prompt);
}
