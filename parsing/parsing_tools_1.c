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

void exec_segment_init(t_segment **exec_segment)
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
	int i;
	int j;
	int	double_quoted;
	int single_quoted;
	int len;

	(1 && (i = 0, j = 0, double_quoted = 0, single_quoted = 0));
	len = ft_strlen(*str);
	while (j < len)
	{
		if((*str)[j] == '"' && !single_quoted)
		{
			toggle(&double_quoted);
			j++;
		}
		else if((*str)[j] == '\'' && !double_quoted)
		{
			toggle(&single_quoted);
			j++;
		}
		else
			(1 && ((*str)[i] = (*str)[j], i++, j++));
	}
	(*str)[i] = '\0';
	return ;
}

char *spaces_to_sep(char *str)
{
	char *new_str;
	int i;

	i = 0;
	new_str = NULL;
	if(!str)
		return (NULL);
	if(is_space(str[0]))
	{
		while (is_space(str[i]) && str[i])
			i++;
	}
	while (str[i])
	{
		if(is_space(str[i]))
		{
			if(!is_space(str[i + 1]) && str[i + 1] != '\0')
				new_str = ft_strjoinc(new_str, SEPARATOR);
		}
		else
			new_str = ft_strjoinc(new_str, str[i]);
		i++;
	}
	return(new_str);
}

char	*handle_dollar_sign(int *i, char *str, t_env *env_list, int double_quoted)
{
	char	*cmd;
	
	cmd = NULL;
	if(!(str[(*i) + 1]) || str[(*i) + 1] == ' ' || (double_quoted && str[(*i) + 1] == '"'))
		return ("$");
	if(str[(*i) + 1] && str[(*i) + 1] == '?')
	{
		cmd = ft_strjoin(cmd, ft_itoa(ft_exit_status(0, GET)));
		return ((*i)++, cmd);
	}
	else if(str[(*i) + 1] && ((str[(*i) + 1] >= 'a' && str[(*i) + 1] <= 'z')
			|| (str[(*i) + 1] >= 'A' && str[(*i) + 1] <= 'Z') || str[(*i) + 1] == '_'))
	{
		expand_helper(&cmd, str, i);
		return (expand_token(cmd, env_list));
	}
	else if(ft_is_digit(str[(*i) + 1]))
		return ((*i)++, NULL);
	if(str[(*i) + 1] && (str[(*i) + 1] == '"' || str[(*i) + 1] == '\'') && !double_quoted)
		return (expand_token(cmd, env_list));
	if (!(str[(*i) + 1] == '\'' || str[(*i) + 1] == '"'))
		return((*i)++, ft_strjoinc("$", str[(*i)]));
	return ("$");
}