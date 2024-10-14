#include "minishell.h"

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
