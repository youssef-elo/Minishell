#include "minishell.h"

void ft_putstr_fd(char *str, int fd)
{
	while(*str)
	{
		write(fd, str, 1);
		str++;
	}
}
void ft_putstrnl_fd(char *str, int fd)
{
	while(*str)
	{
		write(fd, str, 1);
		str++;
	}
	write(fd, "\n", 1);
}