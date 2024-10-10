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
	t_token	seg_command;
	t_token *output_rdr;
	t_token *input_rdr;
	t_token *seg_args;
	int		args_count;
	int		seg_output_fd;
	int		seg_input_fd;
} t_segment;

int		ft_is_digit(int c);
int		ft_is_alphanum(int c);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
t_token	*list_tokens(char **tokens);
void	*gc_handler(int s ,int action);
int		tokens_counter(const char *cmd);
void	parse(char *str, t_env *env_list);
t_env	*ft_lstnew(void *key, void *value);
char	**split_tokens(const char *s, char c);
char	*ft_strjoinc(const char *s1, const char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	env_stacking(char **env, t_env **env_stack);
char	*ft_substr(const char *s, int start, int len);
void	append_node(t_env **list, char *key, char *value);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
void	append_token(t_token **token_list, char *value, t_token_type type);
#endif