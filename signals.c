#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 2);
		rl_redisplay();
		ft_exit_status(1, SET);
	}
}

void	set_signals(int ign, char **ignore)
{
	ign = (int)ignore;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_set_wait(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_wait);
	signal(SIGQUIT, signal_wait);
}

void	signal_wait(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		write(1, "Quit : 3\n", 9);
}
