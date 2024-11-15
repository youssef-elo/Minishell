#include "minishell.h"

int g_here_sig = 0;

void heredoc_signal(int sig)
{
	if(sig == SIGINT)
	{
		close(0);
		g_here_sig = 1;
	}
}

void expand_line(char **line, t_env *env_list)
{
    char *new_line;
    int i;

    new_line = NULL;
    i = 0;
    while ((*line)[i])
    {
        if((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] != '"' && (*line)[i + 1] != '\'')
            new_line = ft_strjoin(new_line, handle_dollar_sign(&i, (*line), env_list, 0));
        else if((*line)[i] != '$')
            new_line = ft_strjoinc(new_line, (*line)[i]);
        i++; 
    }
    // printf("newline->%s\n", new_line);
	// *ret = new_line;
    (*line) = new_line;
}

int heredoc_launcher(int fd, char *delimiter, t_env *env_list)
{
	char	*ret;
    char	*line;
	int		in_dup;
    int		fd_return;
    int		expandable;

	ret = NULL;
    line = NULL;
	in_dup = dup(0);
    fd_return = -2;
    expandable = 1;
    if(!is_expandable(delimiter))
    {
        expandable = 0;
        dollar_sign_case(&delimiter);
        quotes_omit(&delimiter);
    }
    // printf("DELIMITER-->%s\nEXPANDABLE->%d\n", delimiter, expandable);
	signal(SIGINT, heredoc_signal);
    while(1)
    {
		if (g_here_sig == 1)
			break ;
        line = readline("> ");
		ret = ft_strdup(line);
        if(!line)
            break ;
        if(ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
            && ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			{
				free(line);
    	        break ;
			}
        if(expandable)
            expand_line(&ret, env_list);
        if(ret)
            write(fd, ret, ft_strlen(ret));
        write(fd, "\n", 1);
		free(line);
        line = NULL;
    }
	signal(SIGINT, signal_handler);
	if (g_here_sig == 1)
	{
		dup2(in_dup, 0);
		close(in_dup);
		close(fd);
		ft_exit_status(1, SET);
		return (-1);
	}
	close(in_dup);
    close(fd);
    fd_return = open("/tmp/heredoc_ms", O_RDONLY);
    //Protection ??
    return(fd_return);
}

void	read_l(char **rl, int is, struct termios state)
{
	rl_catch_signals = 0;
	if (is == 1)
	{
		*rl = readline("minishell> ");
		if (!(*rl))
			readline_exit();
	}
	else if (is == 0)
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

int	main(int argc, char **argv, char **env)
{
	int				is;
	char			*rl;
	struct termios	state;
	t_exec			*prompt;
	t_env			*env_list;

	is = isatty(STDIN_FILENO);
	env_list = NULL;
	env_stacking(env, &env_list);
	set_signals(argc, argv);
	tcgetattr(STDIN_FILENO, &state);
	while (1)
	{
		read_l(&rl, is, state);
		prompt = parse(rl, env_list, &env_list);

		if (g_here_sig == 1)
		{
			g_here_sig = 0;
			while(prompt)
			{
				if (prompt->fd_in && prompt->fd_in != -1)
					close(prompt->fd_in);
				if (prompt->fd_out != 1 && prompt->fd_out != -1)
					close(prompt->fd_out);
				prompt = prompt->next;
			}
			gc_handler(0, FREE);
			free(rl);
			rl = NULL;
			continue ;
		}
		main_exec(prompt);
		gc_handler(0, FREE);
		free(rl);
	}
	galloc(0, FREE);
	return (0);
}
