/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:45:03 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/09/21 22:56:50 by yel-ouaz         ###   ########.fr       */
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

int main(int argc, char **argv, char **env)
{
	t_env *env_list;	

	argc = 0;
	argv = 0;
	env_stacking(env, &env_list);
	return 0;
}
