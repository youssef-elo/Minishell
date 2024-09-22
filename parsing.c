/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:00:49 by hrochd            #+#    #+#             */
/*   Updated: 2024/09/22 23:41:50 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void toggle(int *boolean)
{
	if (*boolean)
		*boolean = 0;
	else
		*boolean = 1;
}

void parse(char *str)
{
	int i;
	int double_quoted;
	int single_quoted;
	// char *cmd;
	
	double_quoted = 0;
	single_quoted = 0;
	i = 0;
	while (str[i])
	{
		if(str[i] == '"' && !single_quoted)
			toggle(&double_quoted);
		else if(str[i] == '\'' && !double_quoted)
			toggle(&single_quoted);
		// ft_strjoinc(cmd, str[i]);
		i++;
	}
	if(double_quoted)
		printf("Syntax error: unexpected end of file (unmatched double quote)\n");
	else if(single_quoted)
		printf("Syntax error: unexpected end of file (unmatched single quote)\n");
	else
	{
		// printf("%s\n", cmd);
	}
}
