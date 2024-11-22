#include "../minishell.h"

void	dollar_sign_case(char **str)
{
	int		i;
	int		j;
	char	*new_str;

	if (!(*str))
		return ;
	new_str = NULL;
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] &&
			((*str)[i + 1] == '"' || (*str)[i + j] == '\''))
			i++;
		new_str = ft_strjoinc(new_str, (*str)[i]);
		i++;
	}
	(*str) = ft_strdup(new_str);
	return ;
}

char	*join_in_double_quotes(char c, int is_double)
{
	char	*to_join;

	to_join = NULL;
	to_join = ft_strjoinc(to_join, '"');
	to_join = ft_strjoinc(to_join, c);
	if (is_double)
		to_join = ft_strjoinc(to_join, c);
	to_join = ft_strjoinc(to_join, '"');
	return (to_join);
}

void	is_heredoc(char *str, int i, int *heredoc, int *unexpected_nl)
{
	if (str[i + 1] && str[i + 1] == '<' && str[i + 2] && str[i + 2] != '<')
	{
		i += 2;
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
			*heredoc = 1;
		else
			*heredoc = 0;
	}
	else
		*heredoc = 0;
	*unexpected_nl = 1;
}

void	open_fail_check(int input_fd, int output_fd, char *value)
{
	if (output_fd == -1 || input_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(value);
	}
	ft_exit_status(1, SET);
}

void	open_fail(t_token *tmp, int *i_fd, int *o_fd, t_segment *exec_seg)
{
	open_fail_check(*i_fd, *o_fd, tmp->value);
	if (*i_fd > 1)
		close(*i_fd);
	if (*o_fd > 1)
		close(*o_fd);
	exec_seg->seg_input_fd = -1;
	exec_seg->seg_output_fd = -1;
	return ;
}
