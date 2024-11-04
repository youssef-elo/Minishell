#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *rl;
	t_exec *prompt;
	struct termios status;
	t_env *env_list = NULL;
for( int i =0; env[i]; i++)printf("%s\n", env[i]);
	tcgetattr(STDIN_FILENO, &status);
	argc = 0;
	argv = 0;
	env_stacking(env, &env_list);
	set_signals();
	while (1)
	{
		rl = readline("minishell> ");
		if(rl == NULL)
			exit(ft_exit_status(0, GET));
		if(ft_strlen(rl) > 0)
			add_history(rl);
		if(ft_strncmp(rl, "exit", 4) == 0)
			break;
		prompt = parse(rl, env_list);
		main_exec(prompt);
		gc_handler(0, FREE);
		free(rl);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &status);
	}
	galloc(0, FREE);
	return 0;
}
