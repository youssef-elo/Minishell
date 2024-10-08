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