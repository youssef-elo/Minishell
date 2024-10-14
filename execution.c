#include "minishell.h"

// void execution(t_execution *prompt)
// {

// }

void solo_command(t_execution *prompt)
{
	// dup2(prompt->fd_in, 0);
	// dup2(prompt->fd_out , 1);
	int pid = fork();
	if (pid == -1)
		printf("error\n");
	if (pid == 0)
	{
		execv(ft_strjoin("/bin/", prompt->cmd), prompt->args);
	}
} 

// int main()
// {
// 	t_execution pr = {0};
// 	pr.args = (char *[]){"ls", NULL};
// 	pr.cmd = "ls";
// 	pr.fd_out =1;
// 	pr.fd_in = 0;
// 	solo_command(&pr);
// }