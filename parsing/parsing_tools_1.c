#include "../minishell.h"

void	expand_helper(char **cmd, char *str, int *i)
{
	*cmd = ft_strjoinc(*cmd, str[(*i) + 1]);
	(*i)++;
	while (ft_is_alphanum(str[(*i) + 1]))
	{
		*cmd = ft_strjoinc(*cmd, str[(*i) + 1]);
		(*i)++;
	}
}

void	exec_segment_init(t_segment **exec_segment)
{
	(*exec_segment)->seg_command = NULL;
	(*exec_segment)->rdrs = NULL;
	(*exec_segment)->seg_args = NULL;
	(*exec_segment)->args_count = 0;
	(*exec_segment)->seg_input_fd = 0;
	(*exec_segment)->seg_output_fd = 1;
}

void	quotes_omit(char **str)
{
	int	i;
	int	j;
	int	len;
	int	double_quoted;
	int	single_quoted;

	(1 && (i = 0, j = 0, double_quoted = 0, single_quoted = 0));
	len = ft_strlen(*str);
	while (j < len)
	{
		if ((*str)[j] == -2 && !single_quoted)
		{
			toggle(&double_quoted);
			j++;
		}
		else if ((*str)[j] == -1 && !double_quoted)
		{
			toggle(&single_quoted);
			j++;
		}
		else
		{
			(*str)[i] = (*str)[j];
			i++;
			j++;
		}
	}
	(*str)[i] = '\0';
	return ;
}

char	*spaces_to_sep(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	if (!str)
		return (NULL);
	if (is_space(str[0]))
	{
		while (is_space(str[i]) && str[i])
			i++;
	}
	while (str[i])
	{
		if (is_space(str[i]))
		{
			if (!is_space(str[i + 1]) && str[i + 1] != '\0')
				new_str = ft_strjoinc(new_str, SEPARATOR);
		}
		else
			new_str = ft_strjoinc(new_str, str[i]);
		i++;
	}
	return (new_str);
}

char	*handle_dollar_sign(int *i, char *s, t_env *env, int dbl_qt)
{
	char	*cmd;

	cmd = NULL;
	if (!(s[(*i) + 1]) || s[(*i) + 1] == ' '
		|| (dbl_qt && s[(*i) + 1] == '"'))
		return ("$");
	if (s[(*i) + 1] && s[(*i) + 1] == '?')
	{
		cmd = ft_strjoin(cmd, ft_itoa(ft_exit_status(0, GET)));
		return ((*i)++, cmd);
	}
	else if (s[(*i) + 1] && ((s[(*i) + 1] >= 'a' && s[(*i) + 1] <= 'z')
			|| (s[(*i) + 1] >= 'A'
				&& s[(*i) + 1] <= 'Z') || s[(*i) + 1] == '_'))
	{
		expand_helper(&cmd, s, i);
		return (expand_token(cmd, env));
	}
	else if (ft_is_digit(s[(*i) + 1]))
		return ((*i)++, NULL);
	if (s[(*i) + 1] && (s[(*i) + 1] == '"' || s[(*i) + 1] == '\'') && !dbl_qt)
		return (expand_token(cmd, env));
	if (!(s[(*i) + 1] == '\'' || s[(*i) + 1] == '"'))
		return ((*i)++, ft_strjoinc("$", s[(*i)]));
	return ("$");
}
