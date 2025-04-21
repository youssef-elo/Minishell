/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:53:24 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:53:25 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_env *envi, char *key)
{
	while (envi)
	{
		if (ft_strncmp(key, envi->key, ft_strlen(key) + 1) == 0)
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}

int	ft_pwd(t_exec *prompt)
{
	char	dir[PATH_MAX];
	char	*env_pwd;

	dir[0] = 0;
	getcwd(dir, PATH_MAX);
	if (dir[0] == '/')
	{
		ft_putstrnl_fd(dir, prompt->fd_out);
		return (0);
	}
	else
	{
		env_pwd = ft_getenv(prompt->env, "PWD");
		if (env_pwd)
		{
			ft_putstrnl_fd(env_pwd, prompt->fd_out);
		}
	}
	if (!env_pwd)
	{
		ft_putstr_fd("pwd : error retreiving current directory\n", 2);
		return (1);
	}
	return (0);
}
