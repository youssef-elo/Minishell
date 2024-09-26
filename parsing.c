/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:00:49 by hrochd            #+#    #+#             */
/*   Updated: 2024/09/27 00:47:17 by hrochd           ###   ########.fr       */
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

void omit_spaces(int *i, char *str, char **cmd)
{
	int j;

	j = *i;
	while(str[*i] && is_space(str[*i]))
		(*i)++;
	(*i)--;
	if(str[(*i) + 1] != '\0' && j > 0)
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
}

void toggle(int *boolean)
{
	if (*boolean)
		*boolean = 0;
	else
		*boolean = 1;
}

char *expand_token(char *cmd, t_env *env_list)
{
	int i;
	int cmd_len;
	
	i = 0;
	cmd_len = ft_strlen(cmd);
	while (env_list)
	{
		if(ft_strncmp(cmd, env_list->key, cmd_len + 1) == 0)
		{
			// printf("FOUND KEY IN ENV = %s\n", env_list->value);
			return (env_list->value);
		}
		env_list = env_list->next;
	}
	// printf("KEY DON'T FOUND IN ENV = %s\n", cmd);
	return (NULL);
}

char	*handle_dollar_sign(int *i, char *str, t_env *env_list)
{
	char	*cmd;
	// int		found_non_alphanum;
	
	cmd = NULL;
	// found_non_alphanum = 0;
	// *cmd = ft_strjoinc(*cmd, '$');
	if(str[(*i) + 1] == '"' || str[(*i) + 1] == '\'' || is_space(str[(*i) + 1]) || str[(*i) + 1] == '\0')
		return (cmd);
	(*i)++;
	if(str[(*i)] && (str[(*i)] == '$' || str[(*i)] == '?'))
	{
		cmd = ft_strjoinc(cmd, '$');
		cmd = ft_strjoinc(cmd, str[(*i)]);
		// if(!is_space(str[(*i) + 1]))
		// 	cmd = ft_strjoinc(cmd, SEPARATOR);
		return (cmd);
	}
	while (str[(*i) + 1] && !is_space(str[(*i) + 1]) && str[(*i) + 1] != '"' && str[(*i) + 1] != '\'' && str[(*i) + 1] != '$') 
	{
		// if(!ft_is_alphanum(str[(*i) + 1]) || !ft_is_alphanum(str[*i]))
		// 	found_non_alphanum = 1;
		cmd = ft_strjoinc(cmd, str[*i]);
		(*i)++;
	}
	cmd = ft_strjoinc(cmd, str[*i]);
	// printf("%s(CMD)", cmd);
	
	// if(found_non_alphanum)
	// 	return (ft_strjoin("$", cmd));
	return (expand_token(cmd, env_list));
}

void print_tokens(char *str)
{
	int i = 0;
	while (str[i])
	{
		if(str[i] == SEPARATOR)
			write(1, "~\n", 2);
		else
			write(1, &str[i], 1);
		i++;
	}
	write(1, "~\n", 2);
}

void handle_delimiter(int *i, char **cmd, char *str)
{
	if((*i) != 0 && !is_space(str[*i - 1]))
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
	*cmd = ft_strjoinc(*cmd, str[*i]);
	if(str[*i] == str[*i + 1])
	{
		(*i)++;
		if(str[*i] == '|')
			*cmd = ft_strjoinc(*cmd, SEPARATOR);
		*cmd = ft_strjoinc(*cmd, str[*i]);
	}
	if(str[*i + 1] != '\0' && !is_space(str[*i + 1]) && str[*i + 1] != '|' && str[*i + 1] != '<' && str[*i + 1] != '>')
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
}


void parse(char *str, t_env *env_list)
{
	int i;
	int double_quoted;
	int single_quoted;
	char *cmd;
	
	double_quoted = 0;
	single_quoted = 0;
	cmd = NULL;
	i = 0;
	while (str[i])
	{
		if(str[i] == '"' && !single_quoted)
			toggle(&double_quoted);
		else if(str[i] == '\'' && !double_quoted)
			toggle(&single_quoted);
		else if (is_space(str[i]) && !double_quoted && !single_quoted)
			omit_spaces(&i, str, &cmd);
		else if (!double_quoted && !single_quoted && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
			handle_delimiter(&i, &cmd, str);
		else if(str[i] == '$' && !single_quoted)
			cmd = ft_strjoin(cmd, handle_dollar_sign(&i, str, env_list));
		else
			cmd = ft_strjoinc(cmd, str[i]);
		if(str[i] != '\0')
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
			print_tokens(cmd);
		else
			printf("~\n");
	}
}
