#include "minishell.h"

char *ft_strdup_env(char *str)
{
	int		i;
	int		slen;
	char	*s2;

	i = 0;
	if (!str)
		return (NULL);
	slen = ft_strlen(str) + 1;
	s2 = galloc(slen * sizeof(char), MALLOC);
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
	t_env *temp;
	t_env *new_node;
	
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

char **char_env(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**env_c;

	i = 0;
	tmp = env;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	env_c = gc_handler((i + 1) * sizeof(char *), MALLOC);
	env_c[i] = NULL;
	i = 0;
	while(env)
	{
		env_c[i] = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		env = env->next;
		i++;
	}
	return (env_c);
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*p;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2)
		return (ft_strdup_env(s2));
	if (s2 == NULL && s1)
		return (ft_strdup_env(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = galloc(i + j + 1, MALLOC);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, (i + 1));
	ft_strlcat(p, s2, (i + j + 1));
	return (p);
}