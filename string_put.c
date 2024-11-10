#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	len= 0;
	while (str[len])
		len++;
	write(fd, str, len);
}
void	ft_putstrnl_fd(char *str, int fd)
{
	int	len;

	len= 0;
	while (str[len])
		len++;
	write(fd, str, len);
	write(fd, "\n", 1);
}
