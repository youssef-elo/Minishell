#include "minishell.h"

int	is_builtin(t_exec *prompt)
{
	int	len;

	len = ft_strlen(prompt->cmd) + 1;
	if (!ft_strncmp(prompt->cmd, "echo", len))
		ft_exit_status(ft_echo(prompt), SET);
	else if (!ft_strncmp(prompt->cmd, "pwd", len))
		ft_exit_status(ft_pwd(prompt), SET);
	else if (!ft_strncmp(prompt->cmd, "exit", len))
		ft_exit_status(ft_exit(prompt, 0), SET);
	else if (!ft_strncmp(prompt->cmd, "cd", len))
		ft_exit_status(export_unset_cd(prompt, 3), SET);
	else if (!ft_strncmp(prompt->cmd, "env", len)
		&& ft_getenv(prompt->env, "PATH"))
		ft_exit_status(ft_env(prompt), SET);
	else if (!ft_strncmp(prompt->cmd, "unset", len))
		ft_exit_status(export_unset_cd(prompt, 2), SET);
	else if (!ft_strncmp(prompt->cmd, "export", len))
		ft_exit_status(export_unset_cd(prompt, 1), SET);
	else
		return (0);
	return (1);
}

void	is_builtin_pipe(t_exec *prompt)
{
	int		len;

	len = ft_strlen(prompt->cmd) + 1;
	if (!ft_strncmp(prompt->cmd, "echo", len))
		exit(ft_echo(prompt));
	else if (!ft_strncmp(prompt->cmd, "pwd", len))
		exit(ft_pwd(prompt));
	else if (!ft_strncmp(prompt->cmd, "exit", len))
		exit(ft_exit(prompt, 1));
	else if (!ft_strncmp(prompt->cmd, "cd", len))
		exit(export_unset_cd(prompt, 3));
	else if (!ft_strncmp(prompt->cmd, "env", len)
		&& ft_getenv(prompt->env, "PATH"))
		exit(ft_env(prompt));
	else if (!ft_strncmp(prompt->cmd, "unset", len))
		exit(export_unset_cd(prompt, 2));
	else if (!ft_strncmp(prompt->cmd, "export", len))
		exit(export_unset_cd(prompt, 1));
}
