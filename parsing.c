#include "minishell.h"

int	is_space(char c)
{
	if(c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

void omit_spaces(int *i, char *str, char **cmd)
{
	int j;

	j = *i;
	while(str[*i] && is_space(str[*i]))
		(*i)++;
	(*i)--;
	if(str[(*i) + 1] != '\0' && j > 0)
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
}

void toggle(int *boolean)
{
	if (*boolean)
		*boolean = 0;
	else
		*boolean = 1;
}

char *expand_token(char *cmd, t_env *env_list)
{
	int i;
	int cmd_len;
	
	i = 0;
	cmd_len = ft_strlen(cmd);
	if(!cmd)
		return(NULL);
	while (env_list)
	{
		if(ft_strncmp(cmd, env_list->key, cmd_len + 1) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*handle_dollar_sign(int *i, char *str, t_env *env_list, int double_quoted)
{
	char	*cmd;
	
	cmd = NULL;
	if(str[(*i) + 1] && str[(*i) + 1] == '?')
	{
		cmd = ft_strjoin(cmd, "$?");
		cmd = ft_strjoinc(cmd, SEPARATOR);
		(*i)++;
		return (cmd);
	}
	if(str[(*i) + 1] && ft_is_alphanum(str[(*i) + 1]))
	{
		if(ft_is_digit(str[(*i) + 1]))
			return (NULL);
		while (ft_is_alphanum(str[(*i) + 1]))
		{
			cmd = ft_strjoinc(cmd, str[(*i) + 1]);
			(*i)++;
		}
		return (expand_token(cmd, env_list));
	}
	if((str[(*i) + 1] == '"' || str[(*i) + 1] == '\'') && !double_quoted)
		return (expand_token(cmd, env_list));
	return ("$");
}

void print_tokens(char *str)
{
	int i = 0;
	while (str[i])
	{
		if(str[i] == SEPARATOR)
			write(1, "~", 1);
		else
			write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void handle_delimiter(int *i, char **cmd, char *str)
{
	if((*i) != 0 && !is_space(str[*i - 1]))
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
	*cmd = ft_strjoinc(*cmd, str[*i]);
	if(str[*i] == str[*i + 1])
	{
		(*i)++;
		if(str[*i] == '|')
			*cmd = ft_strjoinc(*cmd, SEPARATOR);
		*cmd = ft_strjoinc(*cmd, str[*i]);
	}
	if(str[*i + 1] != '\0' && !is_space(str[*i + 1]) && str[*i + 1] != '|' && str[*i + 1] != '<' && str[*i + 1] != '>')
		*cmd = ft_strjoinc(*cmd, SEPARATOR);
}

void parse(char *str, t_env *env_list)
{
	int i;
	int double_quoted;
	int single_quoted;
	char *cmd;
	char **tokens;
	t_token *token_list;

	const char* token_types[] = {"CMD", "ARG", "RDR_ARG", "PIPE", "INPUT_R", "OUTPUT_R", "OUTPUT_A", "HEREDOC"};
	
	double_quoted = 0;
	single_quoted = 0;
	cmd = NULL;
	token_list = NULL;
	i = 0;
	if(str[0] == '\0')
		return ;
	while (str[i])
	{
		if(str[i] == '"' && !single_quoted)
			toggle(&double_quoted);
		else if(str[i] == '\'' && !double_quoted)
			toggle(&single_quoted);
		if (is_space(str[i]) && !double_quoted && !single_quoted)
			omit_spaces(&i, str, &cmd);
		else if (!double_quoted && !single_quoted && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
			handle_delimiter(&i, &cmd, str);
		else if(str[i] == '$' && !single_quoted)
			cmd = ft_strjoin(cmd, handle_dollar_sign(&i, str, env_list, double_quoted));
		else
			cmd = ft_strjoinc(cmd, str[i]);
		if(str[i] != '\0')
			i++;
	}
	if(!cmd)
		return;
	cmd = ft_strjoinc(cmd, SEPARATOR);
	if(cmd && double_quoted)
		printf("Syntax error: unexpected end of file (unmatched double quote)\n");
	else if(cmd && single_quoted)
		printf("Syntax error: unexpected end of file (unmatched single quote)\n");
	else
	{
		tokens = split_tokens(cmd, SEPARATOR);
		// int j = 0;
		// while(tokens[j])
		// {
		// 	printf("TOKEN -> {%s}\n", tokens[j]);
		// 	j++;
		// }

		token_list = list_tokens(tokens);

		t_token *temp_tokens_list = token_list;
		while(temp_tokens_list)
		{
			printf("TOKEN VALUE -> {%s} ----- TOKEN TYPE -> {%s}\n", temp_tokens_list->value, token_types[temp_tokens_list->type]);
			temp_tokens_list = temp_tokens_list->next;
		}


	}
}
