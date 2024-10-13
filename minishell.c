#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_env *env_list = NULL;	

	argc = 0;
	argv = 0;
	char *rl;
	env_stacking(env, &env_list);
	// for (;env_list;)
	// {
	// 	printf("%s=%s\n", env_list->key, env_list->value);
	// 	env_list = env_list->next;
	// }
	while (1)
	{
		rl = readline("minishell> ");
		// exec_test(env_list);
		if(rl == NULL)
			break;
		if(ft_strlen(rl) > 0)
			add_history(rl);
		if(ft_strncmp(rl, "exit", 4) == 0)
			break;
		parse(rl, env_list);
	free(rl);
	}
	return 0;
}
