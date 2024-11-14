#ifndef HEADER_YSF_H
# define HEADER_YSF_H

#define SET 0
#define GET 1

typedef struct s_execution t_exec;
typedef unsigned long long ull;
#include <sys/stat.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "header_hamza.h"
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>


typedef struct	s_execution
{
	char				*cmd;
	char				**args;
	t_env				*env;
	t_env				**head;
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


char		*ft_itoa(int n);
int			ft_isspace(int c);
void		readline_exit(void);
int			exit_err(char *str);
int			var_check(char *str);
int			ft_pwd(t_exec *data);
void		signal_wait(int sig);
void		signal_set_wait(void);
void		exec_test(t_env *env); 
char		**char_env(t_env *env);
int			ft_env(t_exec * prompt);
void		signal_handler(int sig);
char		*ft_chrdup(const char c);
int			my_exit(int exit_status);
int			ft_atoi(const char *str);
int			my_exit(int exit_status);
int			ft_exit_check(char *str);
int			ft_echo(t_exec * prompt);
void		shlvl_update(t_env *tmp);
void		main_exec(t_exec *prompt);
char		*ft_strdup_env(char *str);
char		**ft_split(char *s, char c);
void		*galloc(int size, int action);
void		ft_putstr_fd(char *str, int fd);
void		ft_putstr_fd(char *str, int fd);
long long	exit_atoi(char *str, int *check);
t_export	*exp_node(char *key, char *value);
void		ft_putstrnl_fd(char *str, int fd);
int			ft_exit(t_exec * prompt, int pipe);
char		*ft_strjoin_env(char *s1, char *s2);
void		set_signals(int ign, char **ignore);
char		*ft_getenv(t_env *envi , char *key);
void 		gc_node(void *ptr, t_mblock **head);
int			ft_exit_status(int status, int action);
t_env		*ft_lstnew_env(void *key, void *value);
void		export_init(t_env *env, t_export **exp);
int			export_unset_cd(t_exec *prompt, int sw);
int			ft_cd(t_exec * prompt, t_export **head);
int			equal_sign_position(char *var);
void		put_export(t_exec *prompt, t_export *exp);
char		*find_operator(char *str, int *set_append);
int			ft_unset(t_exec * prompt, t_export **head);
int			ft_export(t_exec *prompt, t_export **head);
void		export_append(t_export **head, t_export *node);
void		shlvl_pwd_env(t_env **head, int sp[], char *pwd);
int			ft_strlcat(char *dst, const char *src, int dstsize);
int			ft_strchrcat(char *dst, const char *src, int dstsize);
void		append_node_env(t_env **list, char *key, char *value);
void		export_var(t_exec *prompt, t_export **head, int *check);
void		ft_substr_exp(char *str, char **key, char **value, int set_apnd);
void		update_append_env(t_env **env, int set_apnd, char *key, char *value);
void		update_append_exp(t_export **exp, int set_apnd, char *key, char *value);
void		export_sort(t_export **head, t_export *node, t_export *tm, t_export *pr);
#endif
