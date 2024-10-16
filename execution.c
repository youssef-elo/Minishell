#include "minishell.h"

// void execution(t_exec *prompt)
// {

// }

void ft_relative_absolute(t_exec *prompt)
{
	if(access(prompt->cmd, X_OK))
	{
		perror(prompt->cmd);
		return ;
	}

}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path 
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

// int is_builtin(t_exec *prompt)
// {
// 	int len;

// 	len = ft_strlen(prompt->cmd) + 1;
// 	if (ft_strncmp(prompt->cmd, "echo", len))
// 		ft_echo(prompt);
// 	else if(ft_strncmp(prompt->cmd, "pwd", len))
// 		ft_pwd(prompt);
// 	else if(ft_strncmp(prompt->cmd, "exit", len))
// 		ft_exit(prompt);
// 	else if(ft_strncmp(prompt->cmd, "cd", len))
// 		ft_cd(prompt);
// 	else if(ft_strncmp(prompt->cmd, "env", len))
// 		ft_env(prompt);
// 	else if(ft_strncmp(prompt->cmd, "unset", len))
// 		ft_unset(prompt);
// 	else if(ft_strncmp(prompt->cmd, "export", len))
// 		ft_export(prompt);
// 	else 
// 		return 0;
// 	return 1;
// }

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

void exec_comm(t_exec *prompt, char *path)
{
	int f;

	f = fork();
	if (f == 0)
	{
		dup2(prompt->fd_in, 0);
		dup2(prompt->fd_out, 1);
		execv(path, prompt->args);
	}
	
}

void solo_command(t_exec *prompt)
{
	char *path;

	// if (is_builtin(prompt))
	// 	return ;
	if ((prompt->cmd[0] == '.' && prompt->cmd[1] == '/') || prompt->cmd[0] == '/')
		exec_comm(prompt, prompt->cmd);
	else
	{
		path = get_path(prompt->cmd, ft_getenv(prompt->env, "PATH"));
		if (path)
		{
			exec_comm(prompt, path);
			return ;
		}
	}
	ft_putstr_fd(prompt->cmd, 2);
	ft_putstr_fd(" : command not found", 2);
}
#include <fcntl.h>

int main(int argc, char **argv, char **env){
	t_exec pr = {0};
	t_env *head = NULL;
	int fd = open("ft",O_CREAT | O_RDWR, 0777);
	printf("%d\n", fd);
	env_stacking(env, &head);
	pr.cmd = argv[1];
	pr.args = argv + 1;
	pr.fd_out = fd;
	pr.fd_in = 0;
	pr.env = head;
	solo_command(&pr);
}
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
