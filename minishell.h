/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:45:15 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/08/14 04:28:08 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>

typedef struct s_env t_env;

struct s_env
{
	char *key;
	char *value;
	t_env *next;	
};

# define MINISHELL_H

#endif