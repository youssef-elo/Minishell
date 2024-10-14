#include "minishell.h"

char *ft_strdup_env(char *str)
{
	int	i;
	int	slen;
	char	*s2;

	i = 0;
	slen = ft_strlen(str) + 1;
	s2 = galloc(slen * sizeof(char), MALLOC);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, str, slen);
	return (s2);
}
t_env	*ft_lstnew_env(void *key, void *value)
{
	t_env	*node;


	node = galloc(sizeof(t_env), MALLOC);
	if (!node)
		return (NULL);
	node->key = ft_strdup_env(key);
	node->value = ft_strdup_env(value);
	node->next = NULL;
	return (node);
}
void append_node_env(t_env **list, char *key, char *value)
{
	t_env *new_node;
	t_env *temp;
	
	if(!list)
		return ;
	new_node = ft_lstnew_env(key, value);
	if(*list== NULL)
	{
		*list = new_node;
		return;
	}
	temp = *list;
	while(temp->next)
		temp = temp->next;
	temp->next = new_node;
}