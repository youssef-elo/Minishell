/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:45:03 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/09/22 22:45:59 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_env *env_list;	

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
		parse(rl);
	}
	free(rl);
	return 0;
}
