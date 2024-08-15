/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 04:19:47 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/08/15 23:42:15 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_quotes(char *line)
{
	int i;
	int doubl;
	int single;

	i = 0;
	doubl = 0;
	single = 0;
	while(line[i])
	{
		if (line[i] == '\'')
			single++;
		if (line[i] == '\"')
			doubl++;
		i++;
	}
	if (doubl % 2 != 0)
		printf("ERROR : unclosed double quote\n");
	if (single % 2 != 0)
		printf("ERROR : unclosed single quote\n");
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
		if (line)
			add_history(line);
		// clean_up_line(&line);
		check_quotes(line);
		free(line);
	}
}