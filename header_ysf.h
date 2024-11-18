#ifndef HEADER_YSF_H
# define HEADER_YSF_H

# define SET 0
# define GET 1

#define RESET 0
#define CREATE 1

typedef struct s_execution	t_exec;
typedef unsigned long long	t_ull;

# include <sys/stat.h>
# include <stdio.h>
# include <termios.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "header_hamza.h"
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>

typedef struct s_execution
{
	char				*cmd;
	char				**args;
	t_env				*env;
	t_env				**head;
	int					fd_in;
	int					fd_out;
	struct s_execution	*next;
}						t_exec;

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}					t_export;

char	*ft_itoa(int n);
int		ft_isspace(int c);
void	ft_wait(int lastp);
void	readline_exit(void);
int		exit_err(char *str);
int		var_check(char *str);
int		ft_pwd(t_exec *data);
void	signal_set_wait(void);
char	**char_env(t_env *env);
int		ft_env(t_exec *prompt);
void	signal_handler(int sig);
int		ft_echo(t_exec *prompt);
int		solo_pre(t_exec *prompt);
char	*ft_chrdup(const char c);
int		my_exit(int exit_status);
int		ft_atoi(const char *str);
int		my_exit(int exit_status);
int		ft_exit_check(char *str);
void	shlvl_update(t_env *tmp);
int		is_delimiter(char *token);
void	main_exec(t_exec *prompt);
char	*ft_strdup_env(char *str);
int		is_builtin(t_exec *prompt);
void	multi_exec(t_exec *prompt);
char	**ft_split(char *s, char c);
void	multi_exec_fail(t_exec *pr);
void	*galloc(int size, int action);
char	**ft_free(char **words, int j);
int		equal_sign_position(char *var);
void	solo_not_found(t_exec *prompt);
void	ft_putstr_fd(char *str, int fd);
void	is_builtin_pipe(t_exec *prompt);
int		heredoc_exit(int in_dup, int fd);
char	*get_path(char *cmd, char *path);
void	ft_putstrnl_fd(char *str, int fd);
int		ft_exit(t_exec *prompt, int pipe);
char	*ft_getenv(t_env *envi, char *key);
char	*ft_strjoin_env(char *s1, char *s2);
void	set_signals(int ign, char **ignore);
void	solo_exec_fail(t_exec *pr, char *path);
int		heredoc_file(int action, int *read_fd);
int		ft_exit_status(int status, int action);
int		ft_cd(t_exec *prompt, t_export **head);
void	multi_exec_path(t_exec *pr, char *path);
void	export_init(t_env *env, t_export **exp);
int		export_unset_cd(t_exec *prompt, int sw);
void	heredoc_sigint(t_exec *prompt, char **rl);
void	put_export(t_exec *prompt, t_export *exp);
int		ft_unset(t_exec *prompt, t_export **head);
int		ft_export(t_exec *prompt, t_export **head);
char	*find_operator(char *str, int *set_append);
void	export_append(t_export **head, t_export *node);
int		fork_fail(t_exec *prompt, int *pip, int pre_id);
void	fork_fail_cleanup(t_exec *prompt, int pre_pipe);
void	put_multi(char *s1, char *s2, char *s3, int fd);
void	read_l(char **rl, int is, struct termios state);
void	shlvl_pwd_env(t_env **head, int sp[], char *pwd);
int		child_setup(t_exec *prompt, int *pip, int *c_pid);
void	solo_exec(t_exec *prompt, char *path, char **env_c);
int		ft_strlcat(char *dst, const char *src, int dstsize);
void	child_process(t_exec *prompt, int pre_pipe, int *pip);
int		ft_strchrcat(char *dst, const char *src, int dstsize);
void	append_node_env(t_env **list, char *key, char *value);
void	parent_process(t_exec *prompt, int *pre_pipe, int *pip);
void	update_append_env(t_env **env, int set_apnd, char *key, char *value);
void	minishell_setup(int *is, t_env **en_l, char **env, struct termios *st);
void	heredoc_readl(int fd, char *delimiter, t_env *env_list, int expandable);
void	update_append_exp(t_export **exp, int set_apnd, char *key, char *value);

#endif
