/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:45:03 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/08/14 04:57:07 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	slen;
	char	*s2;

	i = 0;
	slen = ft_strlen(s1) + 1;
	s2 = malloc(slen * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, slen);
	return (s2);
}

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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	char	*p;

	if (s == NULL)
		return (NULL);
	i = (size_t)start;
	j = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - i)
		len = slen - i;
	p = (char *)malloc(len + 1);
	if (p == NULL)
		return (NULL);
	while (j < len && s[i])
		p[j++] = s[i++];
	p[j] = '\0';
	return (p);
}

int equal_sign_position(char *var)
{
	int i;

	i = 0;
	while(var[i])
	{
		if(var[i] == '=')
			break;
		i++;
	}
	return (i);
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

void env_stacking(char **env, t_env **env_stack)
{
	int i;
	int j;
	int equal_pos;

	i = 0;
	while(env[i])
	{
		j = 0;
		equal_pos = equal_sign_position(env[i]);
		while(env[i][j])
			j++;
		append_node(env_stack, ft_substr(env[i], 0, equal_pos), ft_substr(env[i], equal_pos + 1, j - equal_pos));
		i++;
	}
}


int main(int argc, char const *argv[], char **env)
{
	t_env *env_stack;	
	env_stacking(env, &env_stack);
	t_env *temp;
	temp = env_stack;
	while (temp)
	{
		printf("key : %s ----> value : %s\n", temp->key, temp->value);
		temp = temp->next;
	}
	system("leaks a.out");
	
	return 0;
}
