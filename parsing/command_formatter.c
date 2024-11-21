#include "../minishell.h"

void	unmatched_quote_error(t_flags *flags)
{
	if (flags->double_quoted)
	{
		write(2, "Syntax error: unexpected end of file (unmatched double quote)\n", 62);
		ft_exit_status(258, SET);
	}
	else if (flags->single_quoted)
	{
		write(2, "Syntax error: unexpected end of file (unmatched single quote)\n", 62);
		ft_exit_status(258, SET);
	}
	return ;
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

void omit_spaces(int *i, char *str, char **cmd)
{
	int j;

	j = *i;
	while(str[*i] && is_space(str[*i]))
		(*i)++;
	(*i)--;
	if(str[(*i) + 1] != '\0' && j > 0)
	{
		if((*cmd) && (*cmd)[ft_strlen(*cmd) - 1] != SEPARATOR)
			*cmd = ft_strjoinc(*cmd, SEPARATOR);
	}
}

void	flagger(char *str, int *i, t_flags *flags)
{
	if(str[*i] == '"' && !flags->single_quoted)
		toggle(&(flags->double_quoted));
	else if(str[*i] == '\'' && !flags->double_quoted)
		toggle(&(flags->single_quoted));
	else if(str[*i] == '<')
		is_heredoc(str, *i, &(flags->heredoc), &(flags->unexpected_nl));
	else if(str[*i] == '>' || str[*i] == '|')
		flags->unexpected_nl = 1;
	return ;
}

void	command_formatter(int *i, char *str, t_flags *flags, t_parsing_vars *pv)
{	
	flagger(str, i, flags);
	if (is_space(str[*i]) && !(flags->double_quoted) && !(flags->single_quoted))
		omit_spaces(i, str, &(pv->cmd));
	else if (!(flags->double_quoted) && !(flags->single_quoted) 
			&& (str[*i] == '|' || str[*i] == '>' || str[*i] == '<'))
		handle_delimiter(i, &(pv->cmd), str);
	else if(str[*i] == '$' && !(flags->single_quoted) && !(flags->heredoc))
		dollar_sign_formatter(i, str, flags, pv);
	else
		pv->cmd = ft_strjoinc(pv->cmd, str[*i]);
	return ;
}

