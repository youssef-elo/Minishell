/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:51:25 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 19:51:26 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_here_sig = 0;

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_here_sig = 1;
	}
}

int	heredoc_launcher(int fd, char *delimiter, t_env *env_list)
{
	char	*ret;
	char	*line;
	int		in_dup;
	int		expandable;

	ret = NULL;
	line = NULL;
	in_dup = dup(0);
	expandable = 1;
	if (!is_expandable(delimiter))
	{
		expandable = 0;
		dollar_sign_case(&delimiter);
		quotes_omit(&delimiter);
	}
	signal(SIGINT, heredoc_signal);
	heredoc_readl(fd, delimiter, env_list, expandable);
	signal(SIGINT, signal_handler);
	if (g_here_sig == 1)
		return (heredoc_exit(in_dup, fd));
	close(in_dup);
	close(fd);
	return (0);
}

void	prompt_reset(struct termios *state)
{
	tcsetattr(0, TCSAFLUSH, state);
	heredoc_file(RESET, NULL);
	gc_handler(0, FREE);
}

int	main(int argc, char **argv, char **env)
{
	int				istty;
	char			*rl;
	struct termios	state;
	t_exec			*prompt;
	t_env			*env_list;

	set_signals(argc, argv);
	minishell_setup(&istty, &env_list, env, &state);
	while (1)
	{
		read_l(&rl, istty, state);
		prompt = parse(rl, env_list, &env_list);
		if (g_here_sig == 1)
		{
			g_here_sig = 0;
			heredoc_sigint(prompt, &rl);
			continue ;
		}
		main_exec(prompt);
		prompt_reset(&state);
		free(rl);
	}
	galloc(0, FREE);
	return (0);
}
