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
	if(!cmd)
		return(NULL);
	while (env_list)
	{
		if(ft_strncmp(cmd, env_list->key, cmd_len + 1) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*handle_dollar_sign(int *i, char *str, t_env *env_list, int double_quoted)
{
	char	*cmd;
	
	cmd = NULL;
	if(str[(*i) + 1] && str[(*i) + 1] == '?')
	{
		cmd = ft_strjoin(cmd, "$?");
		cmd = ft_strjoinc(cmd, SEPARATOR);
		(*i)++;
		return (cmd);
	}
	if(str[(*i) + 1] && ft_is_alphanum(str[(*i) + 1]))
	{
		if(ft_is_digit(str[(*i) + 1]))
			return (NULL);
		while (ft_is_alphanum(str[(*i) + 1]))
		{
			cmd = ft_strjoinc(cmd, str[(*i) + 1]);
			(*i)++;
		}
		return (expand_token(cmd, env_list));
	}
	if((str[(*i) + 1] == '"' || str[(*i) + 1] == '\'') && !double_quoted)
		return (expand_token(cmd, env_list));
	return ("$");
}

void print_tokens(char *str)
{
	int i = 0;
	while (str[i])
	{
		if(str[i] == SEPARATOR)
			write(1, "~", 1);
		else
			write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
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

int syntax_err_checker(t_token *token_list)
{
	t_token *tmp;
	int		err;

	tmp = token_list;
	err = 1;
	if(token_list->type == PIPE)
		return(write(2, "syntax error near unexpected token `|'\n", 39));
	while (tmp)
	{
		if(tmp->type == PIPE)
		{
			if(err == 1)
				return(write(2, "syntax error near unexpected token `|'\n", 39));
			else
				err = 1;
		}
		if(tmp->type == ARG || tmp->type == CMD || tmp->type == RDR_ARG)
			err = 0;
		tmp = tmp->next;
	}
	if(err)
		return(write(2, "syntax error near unexpected token `newline'\n", 45));
	else
		return (0);
}

void	quotes_omit(char **str)
{
	int i;
	int j;
	int	double_quoted;
	int single_quoted;
	int len;

	i = 0;
	j = 0;
	double_quoted = 0;
	single_quoted = 0;
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
		{
			(*str)[i] = (*str)[j];
			i++;
			j++;
		}
	}
	(*str)[i] = '\0';
	return ;
}

void	tokens_quotes_omit(t_token **list)
{
	t_token *tokens;

	tokens = *list;
	while (tokens)
	{
		quotes_omit(&tokens->value);
		tokens = tokens->next;
	}
	
}

void exec_segment_init(t_execution *exec_segment)
{
	exec_segment->cmd = NULL;
	exec_segment->args = NULL;
	exec_segment->fd_in = 0;
	exec_segment->fd_out = 1;
	exec_segment->next = NULL;
}

t_segment	*segments_definer(t_token *token_list)
{
	t_token *temp;
	t_execution *exec_segments;

	temp = token_list;
	exec_segments_init(exec_segments);
	while (temp)
	{
		if(temp->type == CMD)
			exec_segments->cmd = ft_strdup(temp->value);
		temp = temp->next;
	}
	
}


void parse(char *str, t_env *env_list)
{
	int i;
	int double_quoted;
	int single_quoted;
	char *cmd;
	char **tokens;
	t_token *token_list;
	t_execution *exec_segments;

	const char* token_types[] = {"CMD", "ARG", "RDR_ARG", "PIPE", "INPUT_R", "OUTPUT_R", "OUTPUT_A", "HEREDOC"};
	
	exec_segments->cmd = NULL;
	exec_segments->args = NULL;
	exec_segments->fd_in = 0;
	exec_segments->fd_out = 1;
	exec_segments->next = NULL;
	double_quoted = 0;
	single_quoted = 0;
	cmd = NULL;
	token_list = NULL;
	i = 0;
	if(str[0] == '\0')
		return ;
	while (str[i])
	{
		if(str[i] == '"' && !single_quoted)
			toggle(&double_quoted);
		else if(str[i] == '\'' && !double_quoted)
			toggle(&single_quoted);
		if (is_space(str[i]) && !double_quoted && !single_quoted)
			omit_spaces(&i, str, &cmd);
		else if (!double_quoted && !single_quoted && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
			handle_delimiter(&i, &cmd, str);
		else if(str[i] == '$' && !single_quoted)
			cmd = ft_strjoin(cmd, handle_dollar_sign(&i, str, env_list, double_quoted));
		else
			cmd = ft_strjoinc(cmd, str[i]);
		if(str[i] != '\0')
			i++;
	}
	if(!cmd)
		return;
	cmd = ft_strjoinc(cmd, SEPARATOR);
	if(cmd && double_quoted)
		printf("Syntax error: unexpected end of file (unmatched double quote)\n");
	else if(cmd && single_quoted)
		printf("Syntax error: unexpected end of file (unmatched single quote)\n");
	else
	{
		tokens = split_tokens(cmd, SEPARATOR);

		// TOKENS PRINTER WITH TOKEN VALUE

		// int j = 0;
		// while(tokens[j])
		// {
		// 	printf("TOKEN -> {%s}\n", tokens[j]);
		// 	j++;
		// }
		////////////////////////////////////

		token_list = list_tokens(tokens);




		if(syntax_err_checker(token_list))
			return;

		t_token *temp_tokens_listt = token_list;
		while(temp_tokens_listt)
		{
			quotes_omit(&temp_tokens_listt->value);
			temp_tokens_listt = temp_tokens_listt->next;
		}

		// TOKENS PRINTER WITH TOKEN VALUE AND TYPE

		t_token *temp_tokens_list = token_list;
		while(temp_tokens_list)
		{
			printf("TOKEN VALUE -> {%s} ----- TOKEN TYPE -> {%s}\n", temp_tokens_list->value, token_types[temp_tokens_list->type]);
			temp_tokens_list = temp_tokens_list->next;
		}
		//////////////////////////////////////////

		segments_definer(token_list);

	}
}
