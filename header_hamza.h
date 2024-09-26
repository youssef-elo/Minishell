#ifndef HEADER_HAMZA_H
#define HEADER_HAMZA_H


#include <stdio.h>
#include <stdlib.h>
#define MALLOC 1
#define FREE 0
#define SEPARATOR '\x1D'

typedef struct s_env t_env;
struct s_env
{
	char *key;
	char *value;
	t_env *next;
};

typedef struct s_mblock t_mblock;
struct s_mblock
{
	void *ptr;
	t_mblock *next;
};

int		ft_is_alphanum(int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	parse(char *str, t_env *env_list);
void	*gc_handler(size_t s ,int action);
t_env	*ft_lstnew(void *key, void *value);
char	*ft_strjoinc(const char *s1, const char c);
void	env_stacking(char **env, t_env **env_stack);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	append_node(t_env **list, char *key, char *value);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(const char *s, unsigned int start, size_t len);


#endif