#include "../minishell.h"

int	is_redir_arg(char *cmd, int i)
{
	int	ret;

	((1) && (i = 0, ret = 0));
	if (cmd)
	{
		while (cmd[i])
		{
			if (cmd[i] == '>' || cmd[i] == '<')
			{
				if ((cmd[i] == '>' && cmd[i + 1] == '>')
					&& ((i >= 1 && cmd[i - 1] != '"')
						|| (cmd[i + 1] && cmd[i + 2] != '"')))
				{
					ret = 1;
					i++;
				}
				else if ((i >= 1 && cmd[i - 1] != '"') || cmd[i + 1] != '"')
					ret = 1;
			}
			else if (cmd[i] != SEPARATOR && !ft_isspace(cmd[i]))
				ret = 0;
			i++;
		}
	}
	return (ret);
}

char	*delimiter_check(char *s)
{
	int		i;
	char	*new_s;

	new_s = NULL;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			if (s[i + 1] && s[i] == s[i + 1] && s[i + 1] != '|')
				join_in_double_quotes(s[i], 1);
			else
				join_in_double_quotes(s[i], 0);
		}
		else
			new_s = ft_strjoinc(new_s, s[i]);
		i++;
	}
	return (new_s);
}

int	next_element_pipe(char *str, int *i)
{
	int	j;

	j = *i;
	j++;
	if (!str[j])
		return (1);
	while (ft_isspace(str[j]))
		j++;
	if (!str[j])
		return (1);
	if (str[j] == '|')
	{
		while (ft_isspace(str[j]))
			j++;
		if (str[j])
			return (1);
	}
	return (0);
}

int	last_element_pipe(char *cmd)
{
	int	i;
	int	is_pipe;

	i = 0;
	is_pipe = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			is_pipe = 1;
		else if (cmd[i] != SEPARATOR)
			is_pipe = 0;
		i++;
	}
	return (is_pipe);
}

void	dollar_sign_formatter(int *i, char *s, t_flags *f, t_parsing_vars *pv)
{
	int		j;
	char	*to_join;
	char	*temp_str;

	(1 && (to_join = NULL, j = 0));
	temp_str = NULL;
	if (f->double_quoted)
	{
		to_join = handle_dollar_sign(i, s, pv->env_list, f->double_quoted);
		pv->cmd = ft_strjoin(pv->cmd, to_join);
	}
	else
	{
		temp_str = handle_dollar_sign(i, s, pv->env_list, f->double_quoted);
		if (temp_str == NULL)
		{
			if (((!(pv->cmd) || last_element_pipe(pv->cmd))
					&& next_element_pipe(s, i)) || is_redir_arg(pv->cmd, j))
				pv->cmd = ft_strjoinc(pv->cmd, EXPAND);
		}
		to_join = spaces_to_sep(temp_str);
		pv->cmd = ft_strjoin(pv->cmd, delimiter_check(to_join));
	}
	f->unexpected_nl = 0;
	return ;
}
