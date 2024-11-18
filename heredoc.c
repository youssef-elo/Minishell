#include "minishell.h"

int	heredoc_file(int action, int *read_fd)
{
	static unsigned int	i;
	int					fd;
	char				*name;
	struct stat			state;

	if (action == CREATE)
	{
		name = ft_strjoin("/tmp/", ft_strjoin("laboursemchat", ft_itoa(i)));
		if (!stat(name, &state))
		{
			i++;
			return (heredoc_file(CREATE, read_fd));
		}
		*read_fd = open(name, O_RDONLY | O_CREAT | O_TRUNC, 0644);
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (heredoc_file(CREATE, read_fd));
		unlink(name);
		i++;
		return (fd);
	}
	else if (action == RESET)
		i = 0;
	return (0);
}

void	expand_line(char **line, t_env *env)
{
	int		i;
	char	*nline;

	i = 0;
	nline = NULL;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1]
			&& (*line)[i + 1] != '"' && (*line)[i + 1] != '\'')
			nline = ft_strjoin(nline, handle_dollar_sign(&i, (*line), env, 0));
		else if ((*line)[i] != '$')
			nline = ft_strjoinc(nline, (*line)[i]);
		i++;
	}
	(*line) = nline;
}

void	heredoc_readl(int fd, char *delimiter, t_env *env_list, int expandable)
{
	char	*ret;
	char	*line;

	while (1)
	{
		line = readline("> ");
		ret = ft_strdup(line);
		if (!line)
			return ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			return ;
		}
		if (expandable)
			expand_line(&ret, env_list);
		if (ret)
			write(fd, ret, ft_strlen(ret));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
}

int	heredoc_exit(int in_dup, int fd)
{
	dup2(in_dup, 0);
	close(in_dup);
	close(fd);
	ft_exit_status(1, SET);
	return (-1);
}
// int	g_here_sig = 0;

// void	heredoc_signal()
// {
// 	g_here_sig = 1;
// 	rl_on_new_line();
// 	rl_replace_line("" , 0);
// 	write(1, "\n", 1);
// 	rl_redisplay();
// 	close (0);
// }

// int	heredoc_launcher(int fd, char *delimiter, t_env *env_list)
// {
// 	char	*ret;
// 	char	*line;
// 	int		in_dup;
// 	int		fd_return;
// 	int		expandable;

// 	ret = NULL;
// 	line = NULL;
// 	in_dup = dup(0);
// 	fd_return = -2;
// 	expandable = 1;
// 	if(!is_expandable(delimiter))
// 	{
// 		expandable = 0;
// 		dollar_sign_case(&delimiter);
// 		quotes_omit(&delimiter);
// 	}
// 	// printf("DELIMITER-->%s\nEXPANDABLE->%d\n", delimiter, expandable);
// 	while(1)
// 	{
// 		signal(SIGINT, heredoc_signal); // signals
// 		line = readline("> ");
// 		if(!line || g_here_sig)
// 			break ;
// 		// if(ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
// 		// 	&& ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
// 		if (!ft_strncmp(line , delimiter, ft_strlen(delimiter) + 1))
// 		{
// 			free(line);
// 			line = NULL;
// 			break ;
// 		}
// 		if(expandable)
// 			expand_line(line, env_list, &ret);
// 		if(ret)
// 			write(fd, ret, ft_strlen(ret));
// 		write(fd, "\n", 1);
// 		free(line);
// 		line = NULL;
// 	}
// 	// signals
// 	if (g_here_sig == 1)
// 		dup2(in_dup , 0);
// 	set_signals(0 , 0);
// 	close (in_dup);
// 	// end signals
// 	close(fd);
// 	fd_return = open("/tmp/heredoc_ms", O_RDONLY);
// 	//Protection ??
// 	return(fd_return);
// }
