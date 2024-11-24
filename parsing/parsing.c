#include "../minishell.h"

t_exec	*parse(char *str, t_env *env_list, t_env **head)
{
	int				i;
	t_flags			flags;
	t_parsing_vars	pv;

	(1 && (flags.check = 0, flags.heredoc = 0, flags.unexpected_nl = 0));
	(1 && (flags.double_quoted = 0, flags.single_quoted = 0));
	(1 && (pv.exec_segments = NULL, pv.cmd = NULL, pv.token_list = NULL));
	(1 && (pv.env_list = env_list, pv.head = head, i = 0));
	if (str[0] == '\0')
		return (NULL);
	while (str[i])
	{
		command_formatter(&i, str, &flags, &pv);
		if (str[i] != '\0')
			i++;
	}
	if (!(pv.cmd))
		return (NULL);
	if ((pv.cmd)[ft_strlen(pv.cmd) - 1] != SEPARATOR)
		(pv.cmd) = ft_strjoinc((pv.cmd), SEPARATOR);
	
	if ((pv.cmd) && (flags.double_quoted || flags.single_quoted))
		unmatched_quote_error(&flags);
	else
		return (command_parser(&pv, &flags));
	return (NULL);
}
