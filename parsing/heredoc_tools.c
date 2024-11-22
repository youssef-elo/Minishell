#include "../minishell.h"

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

int	heredoc_handler(t_token *tmp, int *in_fd, int *out_fd, t_env *env)
{
	int	hd_file;

	if (*in_fd != 0)
		close(*in_fd);
	hd_file = heredoc_file(CREATE, in_fd);
	if (heredoc_launcher(hd_file, tmp->value, env) == -1)
	{
		close(*in_fd);
		if (*out_fd != 1)
			close(*out_fd);
		return (-1);
	}
	return (0);
}
