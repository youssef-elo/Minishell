/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:53:10 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:53:11 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_exec *prompt)
{
	char	**env_c;
	int		i;

	i = 0;
	env_c = char_env(prompt->env);
	if (!env_c)
		return (0);
	while (env_c[i])
	{
		ft_putstrnl_fd(env_c[i], prompt->fd_out);
		i++;
	}
	return (0);
}
