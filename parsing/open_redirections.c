#include "../minishell.h"

void	fd_assigner(int amb, t_segment *exec, int in_fd, int out_fd)
{
	if (amb)
	{
		if (in_fd > 1)
			close(in_fd);
		if (out_fd > 1)
			close(out_fd);
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		ft_exit_status(1, SET);
	}
	exec->seg_input_fd = in_fd;
	exec->seg_output_fd = out_fd;
}

void	redirection_opener(t_token *temp, int *input_fd, int *output_fd)
{
	if (temp->type == OUTPUT_R)
		*output_fd = open(temp->value, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (temp->type == OUTPUT_A)
		*output_fd = open(temp->value, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (temp->type == INPUT_R)
		*input_fd = open(temp->value, O_RDONLY);
}

void	fd_closer(t_token *temp, int *input_fd, int *output_fd)
{
	if (*output_fd > 1 && (temp->type == OUTPUT_R || temp->type == OUTPUT_A))
		close(*output_fd);
	else if (*input_fd != 0 && temp->type == INPUT_R)
		close(*input_fd);
}

int	rdr_hndl(t_token *tmp, int *input_fd, int *output_fd, int *amb)
{
	char	*sep;

	sep = ft_chrdup(EXPAND);
	if (tmp->type == OUTPUT_R || tmp->type == OUTPUT_A || tmp->type == INPUT_R)
	{
		fd_closer(tmp, input_fd, output_fd);
		if (!ft_strncmp(tmp->value, sep, ft_strlen(tmp->value)))
		{
			*amb = 1;
			if (tmp->type == OUTPUT_A || tmp->type == OUTPUT_R)
				*output_fd = -1;
			if (tmp->type == INPUT_R)
				*input_fd = -1;
			return (-1);
		}
		redirection_opener(tmp, input_fd, output_fd);
	}
	return (0);
}

void	open_rdrs(t_segment	*exec_segment, t_env *env, int *check)
{
	char		*sep;
	t_token		*t;
	t_rdr_flags	r;

	(1 && (r.input_fd = 0, r.ambiguous = 0, r.output_fd = 1));
	(1 && (sep = ft_chrdup(EXPAND), t = exec_segment->rdrs));
	while (t)
	{
		if (rdr_hndl(t, &(r.input_fd), &(r.output_fd), &(r.ambiguous)) == -1)
			break ;
		else if (t->type == HEREDOC)
		{
			if (heredoc_handler(t, &(r.input_fd), &(r.output_fd), env) == -1)
			{
				*check = -1;
				return ;
			}
		}
		if (r.input_fd == -1 || r.output_fd == -1)
			break ;
		t = t->next;
	}
	if (t && !(r.ambiguous))
		return (open_fail(t, &(r.input_fd), &(r.output_fd), exec_segment));
	fd_assigner(r.ambiguous, exec_segment, r.input_fd, r.output_fd);
}
