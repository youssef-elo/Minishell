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