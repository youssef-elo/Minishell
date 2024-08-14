#ifndef HEADER_HAMZA_H
#define HEADER_HAMZA_H


#include <stdio.h>
#include <stdlib.h>

typedef struct s_env t_env;
struct s_env
{
	char *key;
	char *value;
	t_env *next;	
};

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
t_env	*ft_lstnew(void *key, void *value);
void	append_node(t_env **list, char *key, char *value);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(const char *s, unsigned int start, size_t len);


#endif