#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_env *env_list = NULL;	

	argc = 0;
	argv = 0;
	char *rl;
	env_stacking(env, &env_list);

	while (1)
	{
		rl = readline("minishell> ");
		if(rl == NULL)
			break;
		if(ft_strlen(rl) > 0)
			add_history(rl);
		if(ft_strncmp(rl, "exit", 4) == 0)
			break;
		parse(rl, env_list);
	}
	free(rl);
	return 0;
}
