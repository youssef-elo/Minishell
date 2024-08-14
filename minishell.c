/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:45:03 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/08/14 06:21:25 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int equal_sign_position(char *var)
{
	int i;

	i = 0;
	while(var[i])
	{
		if(var[i] == '=')
			break;
		i++;
	}
	return (i);
}

void env_stacking(char **env, t_env **env_stack)
{
	int i;
	int j;
	int equal_pos;

	i = 0;
	while(env[i])
	{
		j = 0;
		equal_pos = equal_sign_position(env[i]);
		while(env[i][j])
			j++;
		append_node(env_stack, ft_substr(env[i], 0, equal_pos), ft_substr(env[i], equal_pos + 1, j - equal_pos));
		i++;
	}
}


int main(int argc, char const *argv[], char **env)
{
	t_env *env_stack;	
	env_stacking(env, &env_stack);
	t_env *temp;
	temp = env_stack;
	while (temp)
	{
		printf("key : %s ----> value : %s\n", temp->key, temp->value);
		temp = temp->next;
	}
	// system("leaks a.out");
	
	return 0;
}
