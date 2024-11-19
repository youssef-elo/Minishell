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
	{
		if((*cmd) && (*cmd)[ft_strlen(*cmd) - 1] != SEPARATOR)
			*cmd = ft_strjoinc(*cmd, SEPARATOR);
	}
}
void toggle(int *boolean)
{

	if (*boolean)
		*boolean = 0;
	else
		*boolean = 1;
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
		{
			if (!env_list->value[0])
				return (NULL);
			return (env_list->value);
		}

		env_list = env_list->next;
	}
	return (NULL);
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
		(*i)++;
		return (cmd);
	}
	else if(str[(*i) + 1] && ((str[(*i) + 1] >= 'a' && str[(*i) + 1] <= 'z')
			|| (str[(*i) + 1] >= 'A' && str[(*i) + 1] <= 'Z') || str[(*i) + 1] == '_'))
	{
		cmd = ft_strjoinc(cmd, str[(*i) + 1]);
		(*i)++;
		while (ft_is_alphanum(str[(*i) + 1]))
		{
			cmd = ft_strjoinc(cmd, str[(*i) + 1]);
			(*i)++;
		}
		return (expand_token(cmd, env_list));
	}
	else if(ft_is_digit(str[(*i) + 1]))
	{
		(*i)++;
		return (NULL);
	}
	if(str[(*i) + 1] && (str[(*i) + 1] == '"' || str[(*i) + 1] == '\'') && !double_quoted)
		return (expand_token(cmd, env_list));
	if (!(str[(*i) + 1] == '\'' || str[(*i) + 1] == '"'))
	{
		(*i)++;
		return(ft_strjoinc("$", str[(*i)]));
	}
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

// int	is_heredoc(char *str, int i)
// {
// 	int previous_token_i;

// 	previous_token_i = i - 1;
// 	if(i < 2)
// 		return 0;
// 	if(ft_isspace(str[i - 1]))
// 	{
// 		while (ft_isspace(str[i - 1]))
// 			i--;
// 	}
// 	if(str[i - 1] == '<')
// }
// int	write_error()

int syntax_err_checker(t_token *token_list, int *unexpected_nl)
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
		if(*unexpected_nl)
		{
			ft_exit_status(258, SET);
			return(write(2, "syntax error near unexpected token `newline'\n", 45));
		}
		else
		{
			ft_exit_status(1, SET);
			return(write(2, "minishell: ambiguous redirect\n", 31));
		}
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

int is_expandable(char *delimiter)
{
	int i;
	
	i = 0;
	while (delimiter[i])
	{
		if(delimiter[i] == '"' || delimiter[i] == '\'')
			return 0;
		i++;
	}
	return 1;
}

void dollar_sign_case(char **str)
{
	int i;
	int j;
	char *new_str;

	if(!(*str))
		return;
	new_str = NULL;
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if((*str)[i] == '$')
		{
			
			while ((*str)[i + j] == '$')
				j++;
			if((*str)[i + j] && ((*str)[i + j] == '"' || (*str)[i + j] == '\''))
				i++;	
		}
		new_str = ft_strjoinc(new_str, (*str)[i]);
		i++;
	}
	(*str) = ft_strdup(new_str);
	return ;
}


// new code !!!!!!!!!!!!!!!!

// void expand_line(char *line, t_env *env_list, char **ret)
// {
// 	char *new_line;
// 	int i;

// 	new_line = NULL;
// 	i = 0;
// 	while (line[i])
// 	{
// 		if(line[i] == '$' && line[i + 1] && line[i + 1] != '"' && line[i + 1] != '\'')
// 			new_line = ft_strjoin(new_line, handle_dollar_sign(&i, line, env_list, 0));
// 		else if(line[i] != '$')
// 			new_line = ft_strjoinc(new_line, line[i]);
// 		i++; 
// 	}
// 	(*ret) = new_line;
// }

// int heredoc_launcher(int fd, char *delimiter, t_env *env_list)
// {
// 	char	*line;
// 	char	*ret;
// 	int		fd_return;
// 	int		expandable;

// 	line = NULL;
// 	ret = NULL;
// 	fd_return = -2;
// 	expandable = 1;
// 	if(!is_expandable(delimiter))
// 	{
// 		expandable = 0;
// 		dollar_sign_case(&delimiter);
// 		quotes_omit(&delimiter);
// 	}
// 	// printf("DELIMITER-->%s\nEXPANDABLE->%d\n", delimiter, expandable);
// 	while(1)
// 	{
// 		line = readline("> ");
// 		if(!line)
// 			break ;
// 		// if(ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
// 		// 	&& ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
// 		if (!ft_strncmp(line , delimiter, ft_strlen(delimiter) + 1))
// 		{
// 			free(line);
// 			line = NULL;
// 			break ;
// 		}
// 		if(expandable)
// 			expand_line(line, env_list, &ret);
// 		if(ret)
// 			write(fd, ret, ft_strlen(ret));
// 		write(fd, "\n", 1);
// 		free(line);
// 		line = NULL;
// 	}
// 	close(fd);
// 	fd_return = open("/tmp/heredoc_ms", O_RDONLY);
// 	//Protection ??
// 	return(fd_return);
// }
//end of new code !!!!!!!!!!!

// the previous code ---------------------

// void expand_line(char **line, t_env *env_list)
// {
// 	char *new_line;
// 	int i;

// 	new_line = NULL;
// 	i = 0;
// 	while ((*line)[i])
// 	{
// 		if((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] != '"' && (*line)[i + 1] != '\'')
// 			new_line = ft_strjoin(new_line, handle_dollar_sign(&i, (*line), env_list, 0));
// 		else if((*line)[i] != '$')
// 			new_line = ft_strjoinc(new_line, (*line)[i]);
// 		i++; 
// 	}
// 	// printf("newline->%s\n", new_line);
// 	(*line) = ft_strdup(new_line);
// }

// int heredoc_launcher(int fd, char *delimiter, t_env *env_list)
// {
// 	char *line;
// 	int fd_return;
// 	int	expandable;

// 	line = NULL;
// 	fd_return = -2;
// 	expandable = 1;
// 	if(!is_expandable(delimiter))
// 	{
// 		expandable = 0;
// 		dollar_sign_case(&delimiter);
// 		quotes_omit(&delimiter);
// 	}
// 	// printf("DELIMITER-->%s\nEXPANDABLE->%d\n", delimiter, expandable);
// 	while(1)
// 	{
// 		line = readline("> ");
// 		if(!line)
// 			break ;
// 		if(ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
// 			&& ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
// 			break ;
// 		if(expandable)
// 			expand_line(&line, env_list);
// 		if(line)
// 			write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		line = NULL;
// 	}
// 	close(fd);
// 	fd_return = open("/tmp/heredoc_ms", O_RDONLY);
// 	//Protection ??
// 	return(fd_return);
// }

// end of previous code ------------------

void open_fail_check(int input_fd, int output_fd, char *value)
{
	if(output_fd == -1 || input_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(value);
	}
	ft_exit_status(1, SET);
}

void	open_rdrs(t_segment	*exec_segment, t_env *env_list, int *check)
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
		else if(temp->type == HEREDOC)
		{
			if(input_fd != 0)
				close(input_fd);
			input_fd = heredoc_file(CREATE);
			heredoc_launcher(dup(input_fd), temp->value, env_list);
			if (input_fd == -1)
			{
				*check = -1;
				return ;
			}
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

void	append_segment(t_exec	**exec_head, t_segment	*exec_segment, t_env *env_list, int *check)
{
	open_rdrs(exec_segment, env_list, check);
	if (*check == -1)
		return ;
	append_seg(exec_head, exec_segment);
	exec_segment_init(&exec_segment);
}

void	exec_segments_definer(t_token *token_list, t_exec	**exec_head, t_env *env_list, int *check)
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
			exec_segment->seg_command = temp;
		else if(temp->type == ARG)
		{
			append_token(&(exec_segment->seg_args), temp->value, temp->type);
			exec_segment->args_count++;
		}
		else if(temp->type == INPUT_R || temp->type == HEREDOC)
			append_token(&(exec_segment->rdrs), temp->next->value, temp->type);
		else if(temp->type == OUTPUT_R || temp->type == OUTPUT_A)
			append_token(&(exec_segment->rdrs), temp->next->value, temp->type);
		if(temp->type == PIPE || !temp->next)
		{
			append_segment(exec_head, exec_segment, env_list, check);
			if (*check == -1)
				return ;
			exec_segment_init(&exec_segment);
		}
		temp = temp->next;
	}
}
void	expand_toggler(char *s, int i, int *double_quoted, int *single_quoted)
{
	if(s[i] == '"' && !*single_quoted)
		toggle(double_quoted);
	else if(s[i] == '\'' && !*double_quoted)
		toggle(single_quoted);
	return ;
}

void expand(char **token, t_env *env_list)
{
	int 	single_quoted;
	int 	double_quoted;
	int 	i;
	char	*cmd;

	single_quoted = 0;
	double_quoted = 0;
	cmd = NULL;
	i = 0;
	if(!(*token))
		return ;
	while ((*token)[i++])
	{
		expand_toggler((*token), i, &double_quoted, &single_quoted);
		if((*token)[i] == '$' && !single_quoted)
		{
			if(double_quoted)
				cmd = ft_strjoin(cmd, handle_dollar_sign(&i, (*token), env_list, double_quoted));
			else
				cmd = ft_strjoin(cmd, spaces_to_sep(handle_dollar_sign(&i, (*token), env_list, double_quoted)));
		}
		else
			cmd = ft_strjoinc(cmd, (*token)[i]);
	}
	*token = ft_strdup(cmd);
}

void expand_tokens(char **tokens, t_env *env_list)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if(!tokens[j])
		return ;
	while (tokens[j])
	{
		if(j == 0 || ft_strncmp(tokens[j - 1], "<<", 2))
		{
			// printf("test\n");
			expand(&tokens[j], env_list);
		}
		j++;
	}
}

void is_heredoc(char *str, int i, int *heredoc, int *unexpected_nl)
{
	if(str[i + 1] && str[i + 1] == '<' && str[i + 2] && str[i + 2] != '<')
	{
		i += 2;
		while(str[i] && str[i] != '$')
			i++;
		if(str[i] == '$')
			*heredoc = 1;
		else
			*heredoc = 0;
	}
	else
		*heredoc = 0;
	*unexpected_nl = 1;
}

char *join_in_double_quotes(char c, int	is_double)
{
	char *to_join;

	to_join = NULL;
	to_join = ft_strjoinc(to_join, '"');
	to_join = ft_strjoinc(to_join, c);
	if(is_double)
		to_join = ft_strjoinc(to_join, c);
	to_join = ft_strjoinc(to_join, '"');
	return (to_join);
}

char *delimiter_check(char *s)
{
	int 	i;
	char	*new_s;

	new_s = NULL;
	i = 0;
	if(!s)
		return NULL;
	while (s[i])
	{
		if(s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			if(s[i + 1] && s[i] == s[i + 1] && s[i + 1] != '|')
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


void put_env(t_env **head_env, t_exec *prompt)
{
	while (prompt)
	{
		prompt->head = head_env;
		prompt->env = *head_env;
		prompt = prompt->next;
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

void	dollar_sign_formatter(int *i, char *str, t_flags *flags, t_parsing_vars *pv)
{
	char *to_join;
	char *temp_str;

	to_join = NULL;
	temp_str = NULL;
	if(flags->double_quoted)
	{
		to_join = handle_dollar_sign(i, str, pv->env_list, flags->double_quoted);
		pv->cmd = ft_strjoin(pv->cmd, to_join);
	}
	else
	{
		temp_str = handle_dollar_sign(i, str, pv->env_list, flags->double_quoted);
		
		to_join = spaces_to_sep(temp_str);
		pv->cmd = ft_strjoin(pv->cmd, delimiter_check(to_join));
	}
	// flags->unexpected_nl = 0;
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

void	unmatched_quote_error(t_flags *flags)
{
	if(flags->double_quoted)
	{
		write(2, "Syntax error: unexpected end of file (unmatched double quote)\n", 62);
		ft_exit_status(258, SET);
	}
	else if(flags->single_quoted)
	{
		write(2, "Syntax error: unexpected end of file (unmatched single quote)\n", 62);
		ft_exit_status(258, SET);
	}
	return ;
}

t_exec	*command_parser(t_parsing_vars *pv, t_flags *flags)
{
	t_token *prev;
	t_token *temp_tokens_listt;

	pv->tokens = split_tokens(pv->cmd, SEPARATOR);
	pv->token_list = list_tokens(pv->tokens);

	
	t_token *tmp = pv->token_list;
	while (tmp)
	{
		printf("TOKEN VALUE -> %s\n", tmp->value);
		tmp = tmp->next;
	}
	
	
	
	
	if(syntax_err_checker(pv->token_list, &(flags->unexpected_nl)))
		return (NULL);
	temp_tokens_listt = pv->token_list;
	prev = NULL;
	while(temp_tokens_listt)
	{
		if((prev && prev->type != HEREDOC) || !prev)
			quotes_omit(&temp_tokens_listt->value);
		prev = temp_tokens_listt;
		temp_tokens_listt = temp_tokens_listt->next;
	}
	exec_segments_definer(pv->token_list, &(pv->exec_segments), pv->env_list, &(flags->check));
	if (flags->check == -1)
		return (NULL);
	put_env(pv->head, pv->exec_segments);
	return (pv->exec_segments);
}

t_exec	*parse(char *str, t_env *env_list, t_env **head)
{
	int 			i;
	t_flags			flags;
	t_parsing_vars	pv;
	
	(1 && (flags.check = 0, flags.heredoc = 0, flags.unexpected_nl = 0));
	(1 && (flags.double_quoted = 0, flags.single_quoted = 0));
	(1 && (pv.exec_segments = NULL, pv.cmd = NULL, pv.token_list = NULL));
	(1 && (pv.env_list = env_list, pv.head = head, i = 0));
	if(str[0] == '\0')
		return (NULL);
	while (str[i])
	{
		command_formatter(&i, str, &flags, &pv);
		if(str[i] != '\0')
			i++;
	}
	if(!(pv.cmd))
		return (NULL);
	if ((pv.cmd)[ft_strlen(pv.cmd) - 1] != SEPARATOR)
		(pv.cmd) = ft_strjoinc((pv.cmd), SEPARATOR);
	if((pv.cmd) && (flags.double_quoted || flags.single_quoted))
		unmatched_quote_error(&flags);
	else
		return (command_parser(&pv, &flags));
	return (NULL);
}
