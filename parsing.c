/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:00:49 by hrochd            #+#    #+#             */
/*   Updated: 2024/09/23 18:15:57 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	is_space(char c)
{
	if(c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

void omit_spaces(int *i, char *str)
{
	while(str[*i] && is_space(str[*i]))
		(*i)++;
	(*i)--;
}

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
	char *cmd;
	
	double_quoted = 0;
	single_quoted = 0;
	cmd = NULL;
	i = 0;
	if(is_space(str[i]))
	{
		omit_spaces(&i, str);
		i++;
	}	
	while (str[i])
	{
		if(str[i] == '"' && !single_quoted)
			toggle(&double_quoted);
		else if(str[i] == '\'' && !double_quoted)
			toggle(&single_quoted);
		else if (is_space(str[i]) && !double_quoted && !single_quoted)
		{
			omit_spaces(&i, str);
			if(str[i + 1] != '\0')
				cmd = ft_strjoinc(cmd, ' ');
		}
		else if (!double_quoted && !single_quoted && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
		{
			if(!is_space(str[i - 1]))
				cmd = ft_strjoinc(cmd, ' ');
			cmd = ft_strjoinc(cmd, str[i]);
			if(str[i] == str[i + 1])
			{
				i++;
				cmd = ft_strjoinc(cmd, str[i]);
			}
			if (!is_space(str[i + 1]))
				cmd = ft_strjoinc(cmd, ' ');
		}
		else
			cmd = ft_strjoinc(cmd, str[i]);
		i++;
	}
	if(cmd && cmd[i - 1] == ' ')
		cmd[i - 1] = '\0';
	if(cmd && double_quoted)
		printf("Syntax error: unexpected end of file (unmatched double quote)\n");
	else if(cmd && single_quoted)
		printf("Syntax error: unexpected end of file (unmatched single quote)\n");
	else
	{
		if(cmd)
			printf("%s$\n", cmd);
		else
			printf("$\n");
	}
}
