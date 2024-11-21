#ifndef HEADER_HAMZA_H
#define HEADER_HAMZA_H


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define MALLOC 1
#define FREE 0
#define SEPARATOR '\x1D'
#define EXPAND '\x1E'


typedef struct s_rdr_flags
{
	int 	input_fd;
	int 	output_fd;
	int		ambiguous;
}	t_rdr_flags;

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
} t_token_type;

typedef struct s_token t_token;

struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
};

typedef struct s_segment
{
	t_token	*seg_command;
	t_token *rdrs;
	t_token *seg_args;
	int		args_count;
	int		seg_output_fd;
	int		seg_input_fd;
} t_segment;

typedef struct	s_flags
{
	int check;
	int unexpected_nl;
	int  heredoc;
	int double_quoted;
	int single_quoted;
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

int		is_space(char c);
int		ft_is_digit(int c);
void	toggle(int *boolean);
int		ft_is_alphanum(int c);
void	quotes_omit(char **str);
int		ft_strlen(const char *s);
char 	*spaces_to_sep(char *str);
char	*ft_strdup(const char *s1);
t_token	*list_tokens(char **tokens);
void	dollar_sign_case(char **str);
void	ft_putstr_fd(char *s, int fd);
void	*gc_handler(int s ,int action);
int		is_expandable(char *delimiter);
int		tokens_counter(const char *cmd);
char	**split_tokens(const char *s, char c);
void	unmatched_quote_error(t_flags *flags);
void	expand_line(char **line, t_env *env_list);
char	*expand_token(char *cmd, t_env *env_list);
char	*ft_strjoinc(const char *s1, const char c);
void 	exec_segment_init(t_segment **exec_segment);
char	*ft_strjoin(const char *s1, const char *s2);
void	env_stacking(char **env, t_env **env_stack);
char	*ft_substr(const char *s, int start, int len);
char	*join_in_double_quotes(char c, int	is_double);
t_token	*ft_lstnewtoken(void *value, t_token_type type);
t_exec	*parse(char *str, t_env *env_list, t_env **head);
int		ft_strncmp(const char *s1, const char *s2, int n);
t_exec	*command_parser(t_parsing_vars *pv, t_flags *flags);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
void	append_seg(t_exec	**exec_seg_list, t_segment	*seg);
int		heredoc_launcher(int fd, char *delimiter, t_env *env_list);
int		syntax_err_checker(t_token *token_list, int *unexpected_nl);
void	is_heredoc(char *str, int i, int *heredoc, int *unexpected_nl);
void	open_rdrs(t_segment	*exec_segment, t_env *env_list, int *check);
void	open_fail(t_token *tmp, int *i_fd, int *o_fd, t_segment *exec_seg);
void	append_token(t_token **token_list, char *value, t_token_type type);
int		heredoc_handler(t_token *tmp, int *in_fd, int *out_fd, t_env *env);
void	command_formatter(int *i, char *str, t_flags *flags, t_parsing_vars *pv);
char	*handle_dollar_sign(int *i, char *str, t_env *env_list, int double_quoted);
void	dollar_sign_formatter(int *i, char *str, t_flags *flags, t_parsing_vars *pv);

#endif