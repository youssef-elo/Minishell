/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:51:33 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/26 11:04:32 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_l(char **rl, int istty, struct termios state)
{
	rl_catch_signals = 0;
	if (istty == 1)
	{
		*rl = readline("minishell> ");
		if (!(*rl))
			readline_exit();
	}
	else if (istty == 0)
	{
		*rl = readline(NULL);
		if (!(*rl))
		{
			gc_handler(0, FREE);
			galloc(0, FREE);
			exit(ft_exit_status(0, GET));
		}
	}
	if (ft_strlen(*rl) > 0)
		add_history(*rl);
	tcsetattr(STDIN_FILENO, TCSANOW, &state);
}

void	minishell_setup(int *is, t_env **en_l, char **env, struct termios *st)
{
	*en_l = NULL;
	*is = isatty(STDIN_FILENO);
	env_stacking(env, en_l);
	tcgetattr(STDIN_FILENO, st);
}

void	heredoc_sigint(t_exec *prompt, char **rl)
{
	while (prompt)
	{
		if (prompt->fd_in > 1)
			close(prompt->fd_in);
		if (prompt->fd_out > 1)
			close(prompt->fd_out);
		prompt = prompt->next;
	}
	gc_handler(0, FREE);
	free(*rl);
	heredoc_file(RESET, NULL);
	*rl = NULL;
}
