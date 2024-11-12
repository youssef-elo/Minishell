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
	while (ft_isspace(str[i]))
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

long long	exit_atoi(char *str, int *check)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (ft_is_digit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		if (res > LLONG_MAX && sign == 1)
		{
			*check = -1;
			return (255);
		}
		else if (res > (unsigned long long)LLONG_MAX + 1)
		{
			*check = -1;
			return (255);
		}
		i++;
	}
	return ((long long)res * sign);
}

int	ft_exit(t_exec *prompt, int pipe)
{
	int	check;
	int exit_status;

	check = prompt->fd_in;
	if (isatty(STDIN_FILENO) && (pipe || !pipe))
		ft_putstr_fd("exit\n", 1);
	// if (pipe == 0)
	// 	ft_putstr_fd("exit\n", 1);
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
	{
		exit_status = exit_atoi(prompt->args[1], &check);
		if (check == -1)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(prompt->args[1], 2);
			ft_putstr_fd(": numeric argument required}\n", 2);
			my_exit(255);
		}
		return (my_exit(exit_status % 256));
	}
	if (prompt->args[2])
	{
		ft_putstr_fd("minishell: exit : too many arguments\n", 2);
		return (1);
	}
	return (1);
}
