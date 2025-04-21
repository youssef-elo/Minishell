/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:51:23 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/26 10:24:55 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <sys/stat.h>
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>

# define SET 0
# define GET 1
# define RESET 0
# define CREATE 1
# define MALLOC 1
# define FREE 0
# define SEPARATOR '\x1D'
# define EXPAND '\x1E'

typedef unsigned long long	t_ull;
typedef struct s_env		t_env;
typedef struct s_mblock		t_mblock;
typedef struct s_token		t_token;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

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

typedef struct s_rdr_flags
{
	int		input_fd;
	int		output_fd;
	int		ambiguous;
}			t_rdr_flags;

struct s_mblock
{
	void		*ptr;
	t_mblock	*next;
};

typedef enum e_token_type
{
	CMD,
	ARG,
	RDR_ARG,
	PIPE,
	INPUT_R,
	OUTPUT_R,
	OUTPUT_A,
	HEREDOC,
	NIL,
}	t_token_type;

struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
};

typedef struct s_segment
{
	int		args_count;
	int		seg_input_fd;
	int		seg_output_fd;
	t_token	*rdrs;
	t_token	*seg_args;
	t_token	*seg_command;
}			t_segment;

typedef struct s_flags
{
	int	check;
	int	unexpected_nl;
	int	heredoc;
	int	double_quoted;
	int	single_quoted;
}		t_flags;

typedef struct s_parsing_vars
{
	t_exec	*exec_segments;
	t_token	*token_list;
	t_env	*env_list;
	t_env	**head;
	char	*cmd;
	char	**tokens;
}			t_parsing_vars;

char	*ft_itoa(int n);
int		is_space(char c);
int		ft_isspace(int c);
int		ft_is_digit(int c);
void	ft_wait(int lastp);
void	readline_exit(void);
int		exit_err(char *str);
int		var_check(char *str);
int		ft_pwd(t_exec *data);
void	toggle(int *boolean);
int		ft_is_alphanum(int c);
void	signal_set_wait(void);
char	**char_env(t_env *env);
int		ft_env(t_exec *prompt);
void	quotes_omit(char **str);
void	signal_handler(int sig);
int		ft_echo(t_exec *prompt);
int		solo_pre(t_exec *prompt);
char	*ft_chrdup(const char c);
int		my_exit(int exit_status);
int		ft_exit_check(char *str);
void	shlvl_update(t_env *tmp);
int		ft_atoi(const char *str);
int		my_exit(int exit_status);
int		ft_strlen(const char *s);
int		is_delimiter(char *token);
void	main_exec(t_exec *prompt);
char	*ft_strdup_env(char *str);
char	*spaces_to_sep(char *str);
int		is_builtin(t_exec *prompt);
void	multi_exec(t_exec *prompt);
char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);
t_token	*list_tokens(char **tokens);
void	multi_exec_fail(t_exec *pr);
void	dollar_sign_case(char **str);
void	ft_putstr_fd(char *s, int fd);
void	*galloc(int size, int action);
void	*gc_handler(int s, int action);
int		is_expandable(char *delimiter);
char	**ft_free(char **words, int j);
int		equal_sign_position(char *var);
void	solo_not_found(t_exec *prompt);
int		tokens_counter(const char *cmd);
void	ft_putstr_fd(char *str, int fd);
void	is_builtin_pipe(t_exec *prompt);
int		heredoc_exit(int in_dup, int fd);
char	*get_path(char *cmd, char *path);
void	ft_putstrnl_fd(char *str, int fd);
int		ft_exit(t_exec *prompt, int pipe);
char	*ft_getenv(t_env *envi, char *key);
char	*ft_strjoin_env(char *s1, char *s2);
void	set_signals(int ign, char **ignore);
char	**split_tokens(const char *s, char c);
void	unmatched_quote_error(t_flags *flags);
void	solo_exec_fail(t_exec *pr, char *path);
int		heredoc_file(int action, int *read_fd);
int		ft_exit_status(int status, int action);
int		ft_cd(t_exec *prompt, t_export **head);
void	multi_exec_path(t_exec *pr, char *path);
void	export_init(t_env *env, t_export **exp);
int		export_unset_cd(t_exec *prompt, int sw);
void	expand_line(char **line, t_env *env_list);
char	*expand_token(char *cmd, t_env *env_list);
void	heredoc_sigint(t_exec *prompt, char **rl);
void	put_export(t_exec *prompt, t_export *exp);
int		ft_unset(t_exec *prompt, t_export **head);
int		ft_export(t_exec *prompt, t_export **head);
char	*find_operator(char *str, int *set_append);
char	*ft_strjoinc(const char *s1, const char c);
void	exec_segment_init(t_segment **exec_segment);
char	*ft_strjoin(const char *s1, const char *s2);
void	env_stacking(char **env, t_env **env_stack);
char	*ft_substr(const char *s, int start, int len);
char	*join_in_double_quotes(char c, int is_double);
void	export_append(t_export **head, t_export *node);
int		fork_fail(t_exec *prompt, int *pip, int pre_id);
void	fork_fail_cleanup(t_exec *prompt, int pre_pipe);
void	put_multi(char *s1, char *s2, char *s3, int fd);
void	read_l(char **rl, int is, struct termios state);
t_token	*ft_lstnewtoken(void *value, t_token_type type);
t_exec	*parse(char *str, t_env *env_list, t_env **head);
void	shlvl_pwd_env(t_env **head, int sp[], char *pwd);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		child_setup(t_exec *prompt, int *pip, int *c_pid);
int		child_setup(t_exec *prompt, int *pip, int *c_pid);
t_exec	*command_parser(t_parsing_vars *pv, t_flags *flags);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
int		ft_strlcat(char *dst, const char *src, int dstsize);
void	solo_exec(t_exec *prompt, char *path, char **env_c);
int		ft_strlcat(char *dst, const char *src, int dstsize);
int		ft_strchrcat(char *dst, const char *src, int dstsize);
void	append_node_env(t_env **list, char *key, char *value);
void	append_seg(t_exec	**exec_seg_list, t_segment	*seg);
void	child_process(t_exec *prompt, int pre_pipe, int *pip);
void	parent_process(t_exec *prompt, int *pre_pipe, int *pip);
int		heredoc_launcher(int fd, char *delimiter, t_env *env_list);
int		syntax_err_checker(t_token *token_list, int *unexpected_nl);
char	*handle_dollar_sign(int *i, char *s, t_env *env, int dbl_qt);
void	is_heredoc(char *str, int i, int *heredoc, int *unexpected_nl);
void	open_rdrs(t_segment	*exec_segment, t_env *env_list, int *check);
void	open_fail(t_token *tmp, int *i_fd, int *o_fd, t_segment *exec_seg);
void	append_token(t_token **token_list, char *value, t_token_type type);
int		heredoc_handler(t_token *tmp, int *in_fd, int *out_fd, t_env *env);
void	update_append_env(t_env **env, int set_apnd, char *key, char *value);
void	minishell_setup(int *is, t_env **en_l, char **env, struct termios *st);
void	dollar_sign_formatter(int *i, char *s, t_flags *f, t_parsing_vars *pv);
void	command_formatter(int *i, char *str, t_flags *flag, t_parsing_vars *pv);
void	heredoc_readl(int fd, char *delimiter, t_env *env_list, int expandable);
void	update_append_exp(t_export **exp, int set_apnd, char *key, char *value);

#endif