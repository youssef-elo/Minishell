#ifndef HEADER_YSF_H
# define HEADER_YSF_H

#define SET 0
#define GET 1
typedef struct s_execution t_exec;
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "header_hamza.h"
#include <limits.h>
#include <fcntl.h>
#include <signal.h>

typedef struct	s_execution
{
	char				*cmd;
	char				**args;
	t_env				*env;
	int					fd_in;
	int					fd_out;
	struct s_execution	*next;
}						t_exec;

typedef	struct	s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}					t_export;


char	*ft_itoa(int n);
void	set_signals(void);
int		ft_pwd(t_exec *data);
void	exec_test(t_env *env); 
int		ft_cd(t_exec * prompt);
char	**char_env(t_env *env);
int		ft_env(t_exec * prompt);
void	signal_handler(int sig);
int		ft_atoi(const char *str);
int		ft_exit(t_exec * prompt);
int		ft_echo(t_exec * prompt);
void	main_exec(t_exec *prompt);
char	*ft_strdup_env(char *str);
int		ft_unset(t_exec * prompt);
int		ft_export(t_exec * prompt);
char	**ft_split(char *s, char c);
void	*galloc(int size, int action);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstrnl_fd(char *str, int fd);
int		ft_exit_status(int status, int action);
char	*ft_getenv(t_env *envi , char *key);
void 	gc_node(void *ptr, t_mblock **head);
t_env	*ft_lstnew_env(void *key, void *value);
void	append_node_env(t_env **list, char *key, char *value);
#endif