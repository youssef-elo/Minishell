#include "../minishell.h"

int	ft_exit(t_exec *prompt, int pipe)
{
	int	check;
	int	exit_status;

	check = prompt->fd_in;
	if (isatty(STDIN_FILENO) && (pipe || !pipe))
		ft_putstr_fd("exit\n", 1);
	if (!prompt->args[1])
		return (my_exit(ft_exit_status(0, GET)));
	check = ft_exit_check(prompt->args[1]);
	if (check == 1)
		my_exit(exit_err(prompt->args[1]));
	if (check == 0 && !prompt->args[2])
	{
		exit_status = exit_atoi(prompt->args[1], &check);
		if (check == -1)
			my_exit(exit_err(prompt->args[1]));
		return (my_exit(exit_status % 256));
	}
	if (prompt->args[2])
	{
		ft_putstr_fd("minishell: exit : too many arguments\n", 2);
		return (1);
	}
	return (1);
}
