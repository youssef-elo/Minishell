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
}						t_exec;

void	ft_pwd(t_exec *data);
void	exec_test(t_env *env); 
void	ft_cd(t_exec * prompt);
void	ft_env(t_exec * prompt);
void	ft_exit(t_exec * prompt);
void	ft_echo(t_exec * prompt);
char	*ft_strdup_env(char *str);
void	ft_unset(t_exec * prompt);
void	ft_export(t_exec * prompt);
void	*galloc(int size, int action);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstrnl_fd(char *str, int fd);
char	**ft_split(char *s, char c);
char	*ft_getenv(t_env *envi , char *key);
void 	gc_node(void *ptr, t_mblock **head);
t_env	*ft_lstnew_env(void *key, void *value);
void	append_node_env(t_env **list, char *key, char *value);
#endif