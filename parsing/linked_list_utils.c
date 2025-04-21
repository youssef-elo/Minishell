/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:51:54 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:59:41 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnewtoken(void *value, t_token_type type)
{
	t_token	*token;

	token = gc_handler(sizeof(t_token), MALLOC);
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_exec	*ft_lstnewseg(t_segment *seg)
{
	int		i;
	t_exec	*exec_seg;

	i = 0;
	exec_seg = gc_handler(sizeof(t_exec), MALLOC);
	if (!exec_seg)
		return (NULL);
	if (seg->seg_command)
		exec_seg->cmd = ft_strdup(seg->seg_command->value);
	else
		exec_seg->cmd = NULL;
	exec_seg->args = gc_handler((seg->args_count + 2) * sizeof(char *), MALLOC);
	exec_seg->args[i++] = exec_seg->cmd;
	while (seg->seg_args)
	{
		exec_seg->args[i] = ft_strdup(seg->seg_args->value);
		seg->seg_args = seg->seg_args->next;
		i++;
	}
	exec_seg->args[i] = NULL;
	exec_seg->fd_in = seg->seg_input_fd;
	exec_seg->fd_out = seg->seg_output_fd;
	exec_seg->next = NULL;
	return (exec_seg);
}

void	append_token(t_token **token_list, char *value, t_token_type type)
{
	t_token	*temp;
	t_token	*new_token;

	if (!token_list)
		return ;
	new_token = ft_lstnewtoken(value, type);
	if (*token_list == NULL)
	{
		*token_list = new_token;
		return ;
	}
	temp = *token_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

void	append_seg(t_exec	**exec_seg_list, t_segment	*seg)
{
	t_exec	*new_exec_seg;
	t_exec	*temp_seg;

	if (!exec_seg_list)
		return ;
	new_exec_seg = ft_lstnewseg(seg);
	if (*exec_seg_list == NULL)
	{
		*exec_seg_list = new_exec_seg;
		return ;
	}
	temp_seg = *exec_seg_list;
	while (temp_seg->next)
		temp_seg = temp_seg->next;
	temp_seg->next = new_exec_seg;
}
