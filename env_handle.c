/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:04:43 by hrochd            #+#    #+#             */
/*   Updated: 2024/09/21 23:06:07 by hrochd           ###   ########.fr       */
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
