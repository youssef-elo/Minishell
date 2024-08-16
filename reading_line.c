/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 04:19:47 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/08/16 01:22:57 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_quotes(char *line)
{
	int		i;
	char	quote;
	int		opened;

	i = 0;
	quote = 0;
	opened = 0;
	while(line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && opened == 0)
		{
			opened = 1;
			quote = line[i];
		}
		else if (line[i] == quote && opened == 1)
		{
			opened = 0;
			quote = 0;
		}
		i++;
	}
	if (opened == 1 && quote == '\'')
		printf("ERROR : unclosed single quote\n");
	if (opened == 1 && quote == '\"')
		printf("ERROR : unclosed double quote\n");
}

void clean_up_line(char **line)
{
	int i;
	int	len;
	int in_quote;
	
	i = 0;
	len = ft_strlen(*line);
	in_quote = 0;
	while(line[i])
	{
		
	}
}

void get_line(t_env *env)
{
	char *line;

	env = 0;
	while(1)
	{
		line = readline("KTAB > ");
		if (line[0] != '\0')
			add_history(line);
		check_quotes(line);
		free(line);
	}
}