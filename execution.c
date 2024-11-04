#include "minishell.h"

// void execution(t_exec *prompt)
// {

// }

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path 
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

void builtin_fd_op(t_exec * prompt)
{
	int out_f;
	int in_f;

	if (prompt->fd_in != 0)
	{
		in_f = dup(0);
		dup2(prompt->fd_in, 0);
		close(prompt->fd_in);
	}
	if (prompt->fd_out != 1)
	{
		out_f = dup(1);
		dup2(prompt->fd_out, 1);
		close(prompt->fd_out);
	}
}

int	is_builtin(t_exec *prompt)
{
	int	len;
	
	len = ft_strlen(prompt->cmd) + 1;
	if (!ft_strncmp(prompt->cmd, "echo", len))
		ft_exit_status(ft_echo(prompt), SET);
	else if(!ft_strncmp(prompt->cmd, "pwd", len))
		ft_exit_status(ft_pwd(prompt), SET);
	// else if(!ft_strncmp(prompt->cmd, "exit", len))
	// 	ft_exit_status(ft_exit(prompt), SET);
	// else if(!ft_strncmp(prompt->cmd, "cd", len))
	// 	ft_exit_status(ft_cd(prompt), SET);
	else if(!ft_strncmp(prompt->cmd, "env", len))
		ft_exit_status(ft_env(prompt), SET);
	else if(!ft_strncmp(prompt->cmd, "unset", len))
		ft_exit_status(export_unset(prompt, 2), SET);
	else if(!ft_strncmp(prompt->cmd, "export", len))
		ft_exit_status(export_unset(prompt, 1), SET);
	else
		return 0;
	return 1;
}

char	*get_path(char *cmd, char *path)
{
	int		i;
	char	*new_cmd;
	char	*cmd_path;
	char	**path_split;

	i = 0;
	if (!path || !cmd || !(*cmd))
		return (NULL);
	new_cmd = ft_strjoin("/", cmd);
	if (!path)
		return (NULL);
	path_split = ft_split(path , ':');
	while(path_split[i])
	{
		cmd_path = ft_strjoin(path_split[i], new_cmd);
		if (!access(cmd_path, X_OK))
			return (cmd_path);
		i++;
	}
	return (NULL);
}
// close
void	solo_exec(t_exec *prompt, char *path, char **env_c)
{
	int		f;
	int		stat;
	pid_t	pid;

	f = fork();
	if (f == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT,SIG_DFL);
		if (prompt->fd_in != 0)
		{
			dup2(prompt->fd_in, 0);
			close(prompt->fd_in);
		}
		if (prompt->fd_out != 1)
		{
			dup2(prompt->fd_out, 1);
			close(prompt->fd_out);
		}
		execve(path, prompt->args, env_c);
		perror(prompt->cmd);
		if (!access(prompt->cmd, F_OK) && access(prompt->cmd, X_OK))
			ft_exit_status(126, SET);
		else if (access(prompt->cmd, F_OK))
			ft_exit_status(127, SET);
	}
	else
	{
		pid = waitpid(f, &stat, 0);
		if (prompt->fd_in != 0)
			close(prompt->fd_in);
		if (prompt->fd_out != 1)
			close(prompt->fd_out);
		if (WIFSIGNALED(stat))
			ft_exit_status(WTERMSIG(stat) + 128, SET);
		else
			ft_exit_status(WEXITSTATUS(stat), SET);
	}
}

void	solo_command(t_exec *prompt, char **env_c)
{
	char	*path;

	if (is_builtin(prompt))
	{
		if (prompt->fd_in != 0)
			close (prompt->fd_in);
		if (prompt->fd_out != 1)
			close(prompt->fd_out);
		return ;
	}
	if ((prompt->cmd[0] == '.' && prompt->cmd[1] == '/') || prompt->cmd[0] == '/')
	{
		solo_exec(prompt, prompt->cmd, env_c);
		return ;
	}
	else
	{
		path = get_path(prompt->cmd, ft_getenv(prompt->env, "PATH"));
		if (path)
		{
			solo_exec(prompt, path, env_c);
			return ;
		}
	}
	ft_putstr_fd(prompt->cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	if (prompt->fd_in != 0)
		close (prompt->fd_in);
	if (prompt->fd_out != 1)
		close(prompt->fd_out);
	ft_exit_status(127, SET);
}

void	is_builtin_pipe(t_exec *prompt)
{
	int	len;

	len = ft_strlen(prompt->cmd) + 1;
	if (!ft_strncmp(prompt->cmd, "echo", len))
		exit(ft_echo(prompt));
	else if(!ft_strncmp(prompt->cmd, "pwd", len))
		exit(ft_pwd(prompt));
	// else if(!ft_strncmp(prompt->cmd, "exit", len))
	// 	exit(ft_exit(prompt));
	// else if(!ft_strncmp(prompt->cmd, "cd", len))
	// 	exit(ft_cd(prompt));
	else if(!ft_strncmp(prompt->cmd, "env", len))
		exit(ft_env(prompt));
	else if(!ft_strncmp(prompt->cmd, "unset", len))
		exit(export_unset(prompt, 2));
	else if(!ft_strncmp(prompt->cmd, "export", len))
		exit(export_unset(prompt, 1));
}

void	multi_exec(t_exec *prompt)
{
	char	*path;

	is_builtin_pipe(prompt);
	//needs update so that it return what the builtin returns
	if ((prompt->cmd[0] == '.' && prompt->cmd[1] == '/') || prompt->cmd[0] == '/')
	{
		execve(prompt->cmd, prompt->args, char_env(prompt->env));
		perror(prompt->cmd);
		if (!access(prompt->cmd, F_OK) && access(prompt->cmd, X_OK))
			exit (126);
		else if (access(prompt->cmd, F_OK))
			exit (127);
	}
	else
	{
		path = get_path(prompt->cmd, ft_getenv(prompt->env, "PATH"));
		if (path)
		{
			// printf("%s\n", path);
			execve(path, prompt->args, char_env(prompt->env));
			perror(prompt->cmd);
			if (!access(prompt->cmd, F_OK) && access(prompt->cmd, X_OK))
				exit (126);
			else if (access(prompt->cmd, F_OK))
				exit (127);
		}
	}
	ft_putstr_fd(prompt->cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	exit (127);
}

void	ft_wait(int lastp)
{
	pid_t	wpid;
	int		stat;

	wpid = waitpid(-1, &stat, 0);
	while(wpid != -1)
	{
		if (wpid == lastp)
		{
			if(WIFSIGNALED(stat))
				ft_exit_status(WTERMSIG(stat) + 128, SET);
			else
				ft_exit_status(WEXITSTATUS(stat), SET);
		}
		wpid = waitpid(-1, &stat, 0);
	}
}

void	child_process(t_exec *prompt, int pre_pipe, int *pip)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pre_pipe != -1 && prompt->fd_in == 0)
	{
		dup2(pre_pipe, 0);
		close(pre_pipe);
	}
	else if (prompt->fd_in != 0)
	{
		dup2(prompt->fd_in, 0);
		// close(prompt->fd_in);
	}
	if (prompt->next && prompt->fd_out == 1)
		dup2(pip[1], 1);
	else if (prompt->fd_out != 1)
	{
		dup2(prompt->fd_out, 1);
		// close(prompt->fd_out);
	}
	close(pip[0]);
	multi_exec(prompt);
}

int	child_setup(t_exec *prompt, int *pip, int *c_pid)
{
	if (prompt->next)
	{
		if (pipe(pip))
		{
			perror("pipe ");
			return (0);
		}
	}
	*c_pid = fork();
	if (*c_pid == -1)
	{
		perror("fork ");
		return (0);
	}
	return (1);
}

void	multi_commands(t_exec *prompt)
{
	int c_pid;
	int lastp;
	int pip[2];
	int pre_pipe;

	pre_pipe = -1;
	while(prompt)
	{
		if (!child_setup(prompt, pip, &c_pid))
			return ;
		// if (prompt->next)
		// {
		// 	if (pipe(pip))
		// 	{
		// 		perror("pipe ");
		// 		return ;
		// 	}
		// }
		// c_pid = fork();
		// if (c_pid == -1)
		// {
		// 	perror("fork ");
		// 	return ;
		// }
		if (c_pid == 0)
			child_process(prompt, pre_pipe, pip);
		// {
		// 	if (pre_pipe != -1 && prompt->fd_in == 0)
		// 	{
		// 		dup2(pre_pipe, 0);
		// 		close(pre_pipe);
		// 	}
		// 	else if (prompt->fd_in != 0)
		// 	{
		// 		dup2(prompt->fd_in, 0);
		// 		close(prompt->fd_in);
		// 	}
		// 	if (prompt->next && prompt->fd_out == 1)
		// 		dup2(pip[1], 1);
		// 	else if (prompt->fd_out != 1)
		// 	{
		// 		dup2(prompt->fd_out, 1);
		// 		close(prompt->fd_out);
		// 	}
		// 	close(pip[0]);
		// 	multi_exec(prompt);
		// }
		else
		{
			if (pre_pipe != -1)
				close(pre_pipe);
			pre_pipe = dup(pip[0]);
			close(pip[0]);
			close(pip[1]);
			if (prompt->fd_in != 0)
				close (prompt->fd_in);
			if (prompt->fd_out != 1)
				close(prompt->fd_out);
			if (!prompt->next)
				lastp = c_pid;
		}
		prompt = prompt->next;
	}
	ft_wait(lastp);
}

void put_struct(t_exec *prompt)
{
	while (prompt)
	{
		printf("%s\n", prompt->cmd);
		int i =0;
		if (prompt->args)
		for (;prompt->args[i]; i++)
			printf("%s\n", prompt->args[i]);
		printf("%p\n", prompt->args[i]);
		printf("%p\n", prompt->next);
		printf("in : %d\tout : %d\n", prompt->fd_in, prompt->fd_out);
		printf("-------------------------\n");
		prompt = prompt->next;
	}
}
//environement should be revised 
//when a command is executed it should be put in the environemetn variable _
void	main_exec(t_exec *prompt)
{
	// static t_export	*head;
	// static int		f;

	// if (f == 0)
	// {
	// 	export_init(prompt->env, head);
	// 	f = 1;
	// }
	// put_struct(prompt);
	if (!prompt)
		return ;
	if (!prompt->next)
		solo_command(prompt, char_env(prompt->env));
	else
		multi_commands(prompt);
}

// int main(int argc, char **argv, char **env){
// 	t_env *head = NULL;
// 	env_stacking(env, &head);

// 	int fd = open("new", O_RDWR | O_CREAT , 0777);
// 	int fd_in = open("red_in", O_RDWR);
// 	// printf("%d\n", fd);
// 	// char *arg[] = {"echo","-n","hello world", NULL};	
// 	char *arg[] = {"cat", NULL};
// 	char *arg2[] = {"echo","-n","hello world", NULL};	
// 	// char *arg3[] = {"ls", NULL};

// 	t_exec pr = {0};
// 	pr.args = arg;
// 	pr.cmd = arg[0];
// 	pr.fd_out = 1;
// 	pr.fd_in = 0;
// 	pr.env = head;

// 	t_exec second = {0};
// 	pr.next = &second;
// 	second.args = arg2;
// 	second.cmd = arg2[0];
// 	second.fd_out = 1;
// 	second.fd_in = 0;
// 	second.env = head;
// 	second.next = NULL;
// 	// t_exec third = {0};
// 	// solo_command(&second, char_env(head));
// 	// third.args = arg3;
// 	// third.cmd = arg3[0];
// 	// second.next = &third;
// 	// third.fd_out = 1;
// 	// third.fd_in = fd;
// 	// third.env = head;
// 	// third.next = NULL;
// 	// solo_command(&pr, envc);
// 	main_exec(&pr);
// 	int f1 =close(fd);
// 	int f2 = close(fd_in);
// 	// printf("%d\t%d\n", f1, f2);
// 	// printf("%d\n", ft_exit_status(0, GET));

// 	fflush(stdout);
// 	// while (1)
// 	// {
// 	// 	sleep(1);
// 	// }
	
// }
// int main()
// {
// 	t_exec pr = {0};
// 	pr.args = (char *[]){"ls", NULL};
// 	pr.cmd = "ls";
// 	pr.fd_out =1;
// 	pr.fd_in = 0;
// 	solo_command(&pr);
// }
// check builtins 
// check path
//check absolute or relative path
