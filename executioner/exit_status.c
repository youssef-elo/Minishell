#include "../minishell.h"

int	ft_exit_status(int status, int action)
{
	static int	exit_status;

	if (action == SET)
	{
		exit_status = status;
		return (status);
	}
	return (exit_status);
}
