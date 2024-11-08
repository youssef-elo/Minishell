#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char			*rl;
	t_exec			*prompt;
	t_env			*env_list;
	struct termios	state;
	
	env_list = NULL;
	tcgetattr(STDIN_FILENO, &state);
	env_stacking(env, &env_list);
	set_signals(argc , argv);
	while (1)
	{
		rl = readline("minishell> ");
		if(!rl)
			readline_exit();
		if(ft_strlen(rl) > 0)
			add_history(rl);
		prompt = parse(rl, env_list, &env_list);
		main_exec(prompt);
		gc_handler(0, FREE);
		free(rl);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &state);
	}
	galloc(0, FREE);
	return 0;
}
