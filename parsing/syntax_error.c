#include "../minishell.h"

int	syntax_error_printer(int error_num, t_token *token)
{
	if(error_num == 1)
	{
		ft_exit_status(258, SET);
		return(write(2, "syntax error near unexpected token `|'\n", 39));
	}
	else if(error_num == 2)
	{
		write(2, "syntax error near unexpected token `", 37);
		ft_putstrnl_fd(token->next->value, 2);
		ft_exit_status(258, SET);
		return(22);
	}
	else if(error_num == 3)
	{
		ft_exit_status(258, SET);
		return(write(2, "syntax error near unexpected token `newline'\n", 45));
	}
	else if(error_num == 4)
	{
		ft_exit_status(1, SET);
		return(write(2, "minishell: ambiguous redirect\n", 31));
	}
	return (0);
} 

int	syntax_err_loop(t_token *tmp, int *err)
{
	if(tmp->type == PIPE)
	{
		if(*err == 1)
			return (syntax_error_printer(1, NULL));
		else
			*err = 1;
	}
	if(tmp->type == ARG || tmp->type == CMD || tmp->type == RDR_ARG)
		*err = 0;
	if(tmp->type == OUTPUT_A || tmp->type == OUTPUT_R || tmp->type == INPUT_R || tmp->type == HEREDOC)
	{
		if(tmp->next && tmp->next->value && tmp->next->type != RDR_ARG)
			return (syntax_error_printer(2, tmp));
		*err = 1;
	}
	return (0);
}


int syntax_err_checker(t_token *token_list, int *unexpected_nl)
{
	t_token *tmp;
	int		err;

	tmp = token_list;
	err = 1;
	if(token_list->type == PIPE)
		return (syntax_error_printer(1, NULL));
	while (tmp)
	{
		if(syntax_err_loop(tmp, &err))
			return (1);
		tmp = tmp->next;
	}
	if(err)
	{
		if(*unexpected_nl)
			return (syntax_error_printer(3, NULL));
		else
			return (syntax_error_printer(4, NULL));
	}
	else
		return (0);
}