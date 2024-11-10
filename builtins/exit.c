#include "../minishell.h"

int	ft_exit_check(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_is_digit(str[i]))
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	my_exit(int exit_status)
{
	galloc(0, FREE);
	gc_handler(0, FREE);
	exit(exit_status);
	return (exit_status);
}

void	readline_exit(void)
{
	write(1, "exit\n", 5);
	galloc(0, FREE);
	gc_handler(0, FREE);
	exit(ft_exit_status(0, GET));
}

int	ft_exit(t_exec *prompt, int pipe)
{
	int	check;

	check = prompt->fd_in;
	if (pipe == 0)
		ft_putstr_fd("exit\n", 1);
	if (!prompt->args[1])
	{
		return (my_exit(ft_exit_status(0, GET)));
	}
	check = ft_exit_check(prompt->args[1]);
	if (check == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(prompt->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (my_exit(255));
	}
	if (check == 0 && !prompt->args[2])
		return (my_exit(exit_atoi(prompt->args[1]) % 256));
	if (prompt->args[2])
	{
		ft_putstr_fd("minishell: exit : too many arguments\n", 2);
		return (1);
	}
	return (1);
}
