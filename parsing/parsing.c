#include "../minishell.h"



// void print_tokens(char *str)
// {
// 	int i = 0;
// 	while (str[i])
// 	{
// 		if(str[i] == SEPARATOR)
// 			write(1, "~", 1);
// 		else
// 			write(1, &str[i], 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }





// void	tokens_quotes_omit(t_token **list)
// {
// 	t_token *tokens;

// 	tokens = *list;
// 	while (tokens)
// 	{
// 		quotes_omit(&tokens->value);
// 		tokens = tokens->next;
// 	}
// }





// void	expand_toggler(char *s, int i, int *double_quoted, int *single_quoted)
// {
// 	if(s[i] == '"' && !*single_quoted)
// 		toggle(double_quoted);
// 	else if(s[i] == '\'' && !*double_quoted)
// 		toggle(single_quoted);
// 	return ;
// }

// void expand(char **token, t_env *env_list)
// {
// 	int 	single_quoted;
// 	int 	double_quoted;
// 	int 	i;
// 	char	*cmd;

// 	single_quoted = 0;
// 	double_quoted = 0;
// 	cmd = NULL;
// 	i = 0;
// 	if(!(*token))
// 		return ;
// 	while ((*token)[i++])
// 	{
// 		expand_toggler((*token), i, &double_quoted, &single_quoted);
// 		if((*token)[i] == '$' && !single_quoted)
// 		{
// 			if(double_quoted)
// 				cmd = ft_strjoin(cmd, handle_dollar_sign(&i, (*token), env_list, double_quoted));
// 			else
// 				cmd = ft_strjoin(cmd, spaces_to_sep(handle_dollar_sign(&i, (*token), env_list, double_quoted)));
// 		}
// 		else
// 			cmd = ft_strjoinc(cmd, (*token)[i]);
// 	}
// 	*token = ft_strdup(cmd);
// }

// void expand_tokens(char **tokens, t_env *env_list)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	if(!tokens[j])
// 		return ;
// 	while (tokens[j])
// 	{
// 		if(j == 0 || ft_strncmp(tokens[j - 1], "<<", 2))
// 			expand(&tokens[j], env_list);
// 		j++;
// 	}
// }


t_exec	*parse(char *str, t_env *env_list, t_env **head)
{
	int 			i;
	t_flags			flags;
	t_parsing_vars	pv;
	
	(1 && (flags.check = 0, flags.heredoc = 0, flags.unexpected_nl = 0));
	(1 && (flags.double_quoted = 0, flags.single_quoted = 0));
	(1 && (pv.exec_segments = NULL, pv.cmd = NULL, pv.token_list = NULL));
	(1 && (pv.env_list = env_list, pv.head = head, i = 0));
	if(str[0] == '\0')
		return (NULL);
	while (str[i])
	{
		command_formatter(&i, str, &flags, &pv);
		if(str[i] != '\0')
			i++;
	}
	if(!(pv.cmd))
		return (NULL);
	if ((pv.cmd)[ft_strlen(pv.cmd) - 1] != SEPARATOR)
		(pv.cmd) = ft_strjoinc((pv.cmd), SEPARATOR);
	if((pv.cmd) && (flags.double_quoted || flags.single_quoted))
		unmatched_quote_error(&flags);
	else
		return (command_parser(&pv, &flags));
	return (NULL);
}
