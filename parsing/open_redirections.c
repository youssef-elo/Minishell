#include "../minishell.h"

void	fd_assigner(int amb, t_segment *exec, int in_fd, int out_fd)
{
	if (amb)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		ft_exit_status(1, SET);
	}
	exec->seg_input_fd = in_fd;
	exec->seg_output_fd = out_fd;
}

void	redirection_opener(t_token *temp, int *input_fd, int *output_fd)
{
	if(temp->type == OUTPUT_R)
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

int	redirections_handler(t_token *tmp, int *input_fd, int *output_fd, int *amb)
{
	char *sep;

	sep = ft_chrdup(EXPAND);
	if(tmp->type == OUTPUT_R || tmp->type == OUTPUT_A || tmp->type == INPUT_R)
	{
		fd_closer(tmp,  input_fd, output_fd);
		if (!ft_strncmp(tmp->value , sep, ft_strlen(tmp->value)))
		{
			(1 && (*amb = 1, *output_fd = -1));
			return (-1);
		}
		redirection_opener(tmp, input_fd, output_fd);
	}
	return (0);
}

void	open_rdrs(t_segment	*exec_segment, t_env *env_list, int *check)
{
	char		*sep;
	t_token		*temp;
	t_rdr_flags	rf;

	(1 && (rf.input_fd = 0, rf.ambiguous = 0, rf.output_fd = 1));
	(1 && (sep = ft_chrdup(EXPAND), temp = exec_segment->rdrs));
	while(temp)
	{
		if (redirections_handler(temp, &(rf.input_fd), &(rf.output_fd), &(rf.ambiguous)) == -1)
			break;
		else if(temp->type == HEREDOC)
		{
			if (heredoc_handler(temp, &(rf.input_fd), &(rf.output_fd), env_list) == -1)
			{
				*check = -1;
				return ;
			}
			printf("%d\n", rf.input_fd);
		}
		if(rf.input_fd == -1 || rf.output_fd == -1)
			break;
		temp = temp->next;
	}
	if(temp && !(rf.ambiguous))
		return (open_fail(temp, &(rf.input_fd), &(rf.output_fd), exec_segment));
	fd_assigner(rf.ambiguous, exec_segment, rf.input_fd, rf.output_fd);
}
