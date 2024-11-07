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
		cmd = ft_strjoin(cmd, ft_itoa(ft_exit_status(0, GET)));
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
	{
		ft_exit_status(258, SET);
		return(write(2, "syntax error near unexpected token `|'\n", 39));
	}
	while (tmp)
	{
		if(tmp->type == PIPE)
		{
			if(err == 1)
			{
				ft_exit_status(258, SET);
				return(write(2, "syntax error near unexpected token `|'\n", 39));
			}
			else
				err = 1;
		}
		if(tmp->type == ARG || tmp->type == CMD || tmp->type == RDR_ARG)
			err = 0;
		if(tmp->type == OUTPUT_A || tmp->type == OUTPUT_R || tmp->type == INPUT_R || tmp->type == HEREDOC)
		{
			if(tmp->next && tmp->next->value && tmp->next->type != RDR_ARG)
			{
				write(2, "syntax error near unexpected token `", 37);
				ft_putstr_fd(tmp->next->value, 2);
				write(2, "'\n", 2);
				ft_exit_status(258, SET);
				return(22);
			}
			err = 1;
		}
		tmp = tmp->next;
	}
	if(err)
	{
		ft_exit_status(258, SET);
		return(write(2, "syntax error near unexpected token `newline'\n", 45));
	}
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

void exec_segment_init(t_segment **exec_segment)
{
	(*exec_segment)->seg_command = NULL;
	(*exec_segment)->rdrs = NULL;
	(*exec_segment)->seg_args = NULL;
	(*exec_segment)->args_count = 0;
	(*exec_segment)->seg_input_fd = 0;
	(*exec_segment)->seg_output_fd = 1;
}

void open_fail_check(int input_fd, int output_fd, char *value)
{
	if(output_fd == -1 || input_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(value);
	}
	ft_exit_status(1, SET);
}

void	open_rdrs(t_segment	*exec_segment)
{
	int input_fd;
	int output_fd;
	t_token	*temp;

	input_fd = 0;
	output_fd = 1;
	temp = exec_segment->rdrs;
	while(temp)
	{
		if(temp->type == OUTPUT_R)
		{
			if(output_fd != 1)
				close(output_fd);
			output_fd = open(temp->value, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		}
		else if(temp->type == OUTPUT_A)
		{
			if(output_fd != 1)
				close(output_fd);
			output_fd = open(temp->value, O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		else if(temp->type == INPUT_R)
		{
			if(input_fd != 0)
				close(input_fd);
			input_fd = open(temp->value, O_RDONLY);
		}
		if(input_fd == -1 || output_fd == -1)
			break;
		temp = temp->next;
	}
	if(temp)
	{
		open_fail_check(input_fd, output_fd, temp->value);
		if(input_fd > 1)
			close(input_fd);
		if(output_fd > 1)
			close(output_fd);
		exec_segment->seg_input_fd = -1;
		exec_segment->seg_output_fd = -1;
		return ;
	}
	exec_segment->seg_input_fd = input_fd;
	exec_segment->seg_output_fd = output_fd;
}

void	append_segment(t_exec	**exec_head, t_segment	*exec_segment)
{
	open_rdrs(exec_segment);
	append_seg(exec_head, exec_segment);
	exec_segment_init(&exec_segment);
}

void	exec_segments_definer(t_token *token_list, t_exec	**exec_head)
{
	t_token		*temp;
	t_segment	*exec_segment;
	int			is_segment_first;

	temp = token_list;
	is_segment_first = 1;
	exec_segment = gc_handler(sizeof(t_segment), MALLOC);
	exec_segment_init(&exec_segment);
	while (temp)
	{
		if(temp->type == CMD)
		{
			// printf("~FOUND CMD : %s\n", temp->value);
			exec_segment->seg_command = temp;
		}
		else if(temp->type == ARG)
		{
			// printf("~FOUND ARG : %s\n", temp->value);
			append_token(&(exec_segment->seg_args), temp->value, temp->type);
			exec_segment->args_count++;
		}
		else if(temp->type == INPUT_R || temp->type == HEREDOC)
		{
			// printf("~FOUND INPUT REDIRECTION OR HEREDOC FROM : %s\n", temp->next->value);
			append_token(&(exec_segment->rdrs), temp->next->value, temp->type);
		}
		else if(temp->type == OUTPUT_R || temp->type == OUTPUT_A)
		{
			// printf("~FOUND OUTPUT REDIRECTION TO : %s\n", temp->next->value);
			append_token(&(exec_segment->rdrs), temp->next->value, temp->type);
		}
		if(temp->type == PIPE || !temp->next)
		{
			append_segment(exec_head, exec_segment);
			exec_segment_init(&exec_segment);
		}
		temp = temp->next;
	}
}


void put_env(t_env **head_env, t_exec *prompt)
{
	while (prompt)
	{
		prompt->head = head_env;
		prompt->env = *head_env;
		prompt = prompt->next;
	}
}

t_exec	*parse(char *str, t_env *env_list, t_env **head)
{
	int i;
	int double_quoted;
	int single_quoted;
	char *cmd;
	char **tokens;
	t_token *token_list;
	t_exec *exec_segments = NULL;
	t_exec *temp_exec;

	// const char* token_types[] = {"CMD", "ARG", "RDR_ARG", "PIPE", "INPUT_R", "OUTPUT_R", "OUTPUT_A", "HEREDOC"};
	// exec_segments = gc_handler(sizeof(t_exec), MALLOC);
	// exec_segments->cmd = NULL;
	// exec_segments->args = NULL;
	// exec_segments->fd_in = 0;
	// exec_segments->fd_out = 1;
	// exec_segments->next = NULL;
	temp_exec = exec_segments;
	double_quoted = 0;
	single_quoted = 0;
	cmd = NULL;
	token_list = NULL;
	i = 0;
	if(str[0] == '\0')
		return (NULL);
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
		return (NULL);
	cmd = ft_strjoinc(cmd, SEPARATOR);
	if(cmd && double_quoted)
	{
		write(2, "Syntax error: unexpected end of file (unmatched double quote)\n", 62);
		ft_exit_status(258, SET);
	}
	else if(cmd && single_quoted)
	{
		write(2, "Syntax error: unexpected end of file (unmatched single quote)\n", 62);
		ft_exit_status(258, SET);
	}
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
			return (NULL);

		t_token *temp_tokens_listt = token_list;
		while(temp_tokens_listt)
		{
			quotes_omit(&temp_tokens_listt->value);
			temp_tokens_listt = temp_tokens_listt->next;
		}

		// TOKENS PRINTER WITH TOKEN VALUE AND TYPE

		// t_token *temp_tokens_list = token_list;
		// while(temp_tokens_list)
		// {
		// 	printf("TOKEN VALUE -> {%s} ----- TOKEN TYPE -> {%s}\n", temp_tokens_list->value, token_types[temp_tokens_list->type]);
		// 	temp_tokens_list = temp_tokens_list->next;
		// }
		//////////////////////////////////////////

		exec_segments_definer(token_list, &exec_segments);
		put_env(head, exec_segments);
		return (exec_segments);
		// temp_exec = exec_segments;
		// while (temp_exec)
		// {
		// 	printf("\n--------------------------------\n");
		// 	if(temp_exec->cmd)
		// 		printf("CMD: %s\n", temp_exec->cmd);
		// 	if(temp_exec->args)
		// 	{
		// 		int iter = 0;
		// 		while (temp_exec->args[iter])
		// 		{
		// 			printf("ARG : %s\n", temp_exec->args[iter]);
		// 			iter++;
		// 		}
		// 	}
		// 	printf("FD_IN : %d\nFD_OUT : %d\n", temp_exec->fd_in, temp_exec->fd_out);
		// 	printf("\n--------------------------------\n");
		// 	temp_exec = temp_exec->next;
		// }
		
	}
	return NULL;
}
//cmd arg red arg red == segv