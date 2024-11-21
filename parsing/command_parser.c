#include "../minishell.h"

void put_env(t_env **head_env, t_exec *prompt)
{
	char *expand_sep;

	expand_sep = ft_chrdup(EXPAND);
	while (prompt)
	{
		if (!ft_strncmp(prompt->cmd, expand_sep, ft_strlen(prompt->cmd) + 1))
			prompt->cmd = NULL;
		prompt->head = head_env;
		prompt->env = *head_env;
		prompt = prompt->next;
	}
}

void	append_segment(t_exec	**exec_head, t_segment	*exec_segment, t_env *env_list, int *check)
{
	open_rdrs(exec_segment, env_list, check);
	if (*check == -1)
		return ;
	append_seg(exec_head, exec_segment);
	exec_segment_init(&exec_segment);
}

void	tokens_definer(t_token *temp, t_segment *exec_segment)
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
		if(temp->type == CMD || temp->type == ARG
			|| temp->type == INPUT_R || temp->type == HEREDOC
			|| temp->type == OUTPUT_R || temp->type == OUTPUT_A)
			tokens_definer(temp, exec_segment);
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

t_exec	*command_parser(t_parsing_vars *pv, t_flags *flags)
{
	t_token *prev;
	t_token *temp_tokens_listt;

	pv->tokens = split_tokens(pv->cmd, SEPARATOR);
	pv->token_list = list_tokens(pv->tokens);
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