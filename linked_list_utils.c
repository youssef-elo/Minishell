/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 06:16:38 by hrochd            #+#    #+#             */
/*   Updated: 2024/08/15 23:32:27 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(void *key, void *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void append_node(t_env **list, char *key, char *value)
{
	t_env *new_node;
	t_env *temp;
	
	new_node = ft_lstnew(key, value);
	free(key);
	free(value);
	if(*list == NULL)
	{
		*list = new_node;
		return;
	}
	temp = *list;
	while(temp->next)
		temp = temp->next;
	temp->next = new_node;
}