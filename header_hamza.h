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
	int		seg_output_fd;
	int		seg_input_fd;
} t_segment;

int		ft_is_digit(int c);
int		ft_is_alphanum(int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		tokens_counter(const char *cmd);
void	parse(char *str, t_env *env_list);
void	*gc_handler(size_t s ,int action);
t_env	*ft_lstnew(void *key, void *value);
char	**split_tokens(const char *s, char c);
char	*ft_strjoinc(const char *s1, const char c);
void	env_stacking(char **env, t_env **env_stack);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	append_node(t_env **list, char *key, char *value);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(const char *s, unsigned int start, size_t len);


#endif