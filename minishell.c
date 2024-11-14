#include "minishell.h"

void	read_l(char **rl, int is, struct termios state)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &state);
	if (is == 1)
	{
		*rl = readline("minishell> ");
		if (!(*rl))
			readline_exit();
	}
	else if (is == 0)
	{
		*rl = readline(NULL);
		if (!(*rl))
		{
			gc_handler(0, FREE);
			galloc(0, FREE);
			exit(ft_exit_status(0, GET));
		}
	}
	if (ft_strlen(*rl) > 0)
		add_history(*rl);
}

int	main(int argc, char **argv, char **env)
{
	int				is;
	char			*rl;
	struct termios	state;
	t_exec			*prompt;
	t_env			*env_list;

	is = isatty(STDIN_FILENO);
	env_list = NULL;
	tcgetattr(STDIN_FILENO, &state);
	env_stacking(env, &env_list);
	set_signals(argc, argv);
	while (1)
	{
		read_l(&rl, is, state);
		// tcsetattr(STDIN_FILENO, TCSAFLUSH, &state);
		// if (is == 1)
		// {
		// 	rl = readline("minishell> ");
		// 	if(!rl)
		// 	readline_exit();
		// }
		// else if (is == 0)
		// {
		// 	rl = readline(NULL);
		// 	if(!rl)
		// 	{
		// 		gc_handler(0, FREE);
		// 		galloc(0, FREE);
		// 		exit(ft_exit_status(0, GET));
		// 	}
		// }
		// if(ft_strlen(rl) > 0)
		// 	add_history(rl);
		prompt = parse(rl, env_list, &env_list);
		main_exec(prompt);
		gc_handler(0, FREE);
		free(rl);
	}
	galloc(0, FREE);
	return (0);
}
