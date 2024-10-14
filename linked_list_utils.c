#include "minishell.h"

t_env	*ft_lstnew(void *key, void *value)
{
	t_env	*node;

	// node = malloc(sizeof(t_env));
	node = gc_handler(sizeof(t_env), MALLOC);
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

t_token	*ft_lstnewtoken(void *value, t_token_type type)
{
	t_token	*token;

	token = gc_handler(sizeof(t_token), MALLOC);
	if(!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_execution	*ft_lstnewseg(t_segment *seg)
{
	t_execution	*exec_seg;
	int			i;

	i = 0;
	exec_seg = gc_handler(sizeof(t_execution), MALLOC);
	if(!exec_seg)
		return (NULL);
	exec_seg->cmd = ft_strdup(seg->seg_command.value);
	exec_seg->args = (char **)gc_handler((seg->args_count + 1) * sizeof(char *), MALLOC);
	while(i < seg->args_count)
	{
		exec_seg->args[i] = ft_strdup(seg->seg_args[i].value);
		i++;
	}
	exec_seg->fd_in = seg->seg_input_fd;
	exec_seg->fd_out = seg->seg_output_fd;
	exec_seg->next = NULL;
	return (exec_seg);
}

void append_node(t_env **list, char *key, char *value)
{
	t_env *new_node;
	t_env *temp;
	
	if(!list)
		return ;
	new_node = ft_lstnew(key, value);
	// free(key);
	// free(value);
	if( *list== NULL)
	{
		*list = new_node;
		return;
	}
	temp = *list;
	while(temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void append_token(t_token **token_list, char *value, t_token_type type)
{
	t_token	*new_token;
	t_token	*temp;

	if(!token_list)
		return ;
	new_token = ft_lstnewtoken(value, type);
	if(*token_list == NULL)
	{
		*token_list = new_token;
		return ;
	}
	temp = *token_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

void append_seg(t_execution	**exec_seg_list, t_segment	*seg)
{
	t_execution *new_exec_seg;
	t_execution *temp_seg;

	if(!exec_seg_list)
		return ;
	new_exec_seg = ft_lstnewseg(seg);
	if(*exec_seg_list == NULL)
	{
		*exec_seg_list = new_exec_seg;
		return ;
	}
	temp_seg = *exec_seg_list;
	while(temp_seg->next)
		temp_seg = temp_seg->next;
	temp_seg->next = new_exec_seg;	
}
