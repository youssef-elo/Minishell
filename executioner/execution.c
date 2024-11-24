#include "../minishell.h"

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

void	main_exec(t_exec *prompt)
{
	if (!prompt)
		return ;
	if (!prompt->next)
		solo_command(prompt, char_env(prompt->env));
	else
		multi_commands(prompt);
}
