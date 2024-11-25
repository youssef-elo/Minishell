#include "../minishell.h"

void	unmatched_quote_error(t_flags *flags)
{
	if (flags->double_quoted)
	{
		write(2, "Syntax error: unexpected end of ", 33);
		write(2, "file (unmatched double quote)\n", 31);
		ft_exit_status(258, SET);
	}
	else if (flags->single_quoted)
	{
		write(2, "Syntax error: unexpected end of ", 33);
		write(2, "file (unmatched single quote)\n", 31);
		ft_exit_status(258, SET);
	}
	return ;
}

void	handle_delimiter(int *i, char **cmd, char *str)
{
	if ((*i) != 0 && !is_space(str[*i - 1])
		&& (*cmd) && (*cmd)[ft_strlen((*cmd)) - 1] != SEPARATOR)
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
	*cmd = ft_strjoinc(*cmd, str[*i]);
	if (str[*i] == str[*i + 1])
	{
		(*i)++;
		if (str[*i] == '|')
			*cmd = ft_strjoinc(*cmd, SEPARATOR);
		*cmd = ft_strjoinc(*cmd, str[*i]);
	}
	if (str[*i + 1] != '\0' && !is_space(str[*i + 1])
		&& str[*i + 1] != '|' && str[*i + 1] != '<'
		&& str[*i + 1] != '>')
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
}

void	omit_spaces(int *i, char *str, char **cmd)
{
	int	j;

	j = *i;
	while (str[*i] && is_space(str[*i]))
		(*i)++;
	(*i)--;
	if (str[(*i) + 1] != '\0' && j > 0)
	{
		if ((*cmd) && (*cmd)[ft_strlen(*cmd) - 1] != SEPARATOR)
			*cmd = ft_strjoinc(*cmd, SEPARATOR);
	}
}

int	flagger(char *str, int *i, t_flags *flags, t_parsing_vars *pv)
{
	if (str[*i] == '"' && !flags->single_quoted)
	{
		toggle(&(flags->double_quoted));
		pv->cmd = ft_strjoinc(pv->cmd, -2);
		return (1);
	}
	else if (str[*i] == '\'' && !flags->double_quoted)
	{
		toggle(&(flags->single_quoted));
		pv->cmd = ft_strjoinc(pv->cmd, -1);
		return (1);
	}
	else if (str[*i] == '<')
		is_heredoc(str, *i, &(flags->heredoc), &(flags->unexpected_nl));
	else if (str[*i] == '>' || str[*i] == '|')
		flags->unexpected_nl = 1;
	return (0);
}

void	command_formatter(int *i, char *str, t_flags *flag, t_parsing_vars *pv)
{
	if (flagger(str, i, flag, pv))
		return ;
	if (is_space(str[*i]) && !(flag->double_quoted)
		&& !(flag->single_quoted))
		omit_spaces(i, str, &(pv->cmd));
	else if (!(flag->double_quoted) && !(flag->single_quoted)
		&& (str[*i] == '|' || str[*i] == '>' || str[*i] == '<'))
		handle_delimiter(i, &(pv->cmd), str);
	else if (str[*i] == '$' && !(flag->single_quoted) && !(flag->heredoc))
		dollar_sign_formatter(i, str, flag, pv);
	else
	{
		pv->cmd = ft_strjoinc(pv->cmd, str[*i]);
		flag->heredoc = 0;
	}
	return ;
}
