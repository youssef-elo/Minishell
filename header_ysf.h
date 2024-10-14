#ifndef HEADER_YSF_H
# define HEADER_YSF_H

#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "header_hamza.h"
#include <limits.h>


typedef struct s_execution
{
	char				*cmd;
	char				**args;
	t_env				*env;
	int					fd_in;
	int					fd_out;
	struct s_execution	*next;
}						t_execution;

void	exec_test(t_env *env); 
void	ft_pwd(t_execution *data);
void	*galloc(int size, int action);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstrnl_fd(char *str, int fd);
char	*ft_getenv(t_env *envi , char *key);
void 	gc_node(void *ptr, t_mblock **head);
char *ft_strdup_env(char *str);
t_env	*ft_lstnew_env(void *key, void *value);
void append_node_env(t_env **list, char *key, char *value);

#endif