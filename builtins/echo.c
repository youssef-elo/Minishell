#include "../minishell.h"

int	flag_check(char **args)
{
	int i;
	int j;

	i = 1;
	while(args[i])
	{
		j = 0;
		if (args[i][j++] != '-' || !args[i][j])
			return (i);
		else
			while(args[i][j])
			{
				if (args[i][j] != 'n')
					return (i);
				j++;
			}
		i++;
	}
	if (i == 1)
		return (i);
	return (-1);
}

void ft_echo(t_exec *prompt)
{
	int start;
	int nl;
	
	start = flag_check(prompt->args);
	nl = start;
	if (start == -1)
		return;
	while(prompt->args[start])
	{
		ft_putstr_fd(prompt->args[start], prompt->fd_out);
		if (prompt->args[start + 1])
			write(prompt->fd_out, " ", 1);
		start++;
	}
	if (nl == 1)
		write(prompt->fd_out, "\n", 1);
}
// int main(int argc, char *argv[]){
// 	if (argc)
// 	ft_echo(argv);
// 	//check for write errors diferent exit status
// }

//echo -nnnnnnnnnnnn... is acceptable 
//in the -nnnnn as long as its all n its ok 
//any argument that has -n from the first argument up till there is ni more flags is skipped 
//for example echo -n -n -nnnnnnnnn -nnnnnnnnnn -nnnnf arguments 
//the only args that will be printed are the last two the first 4 are considered flags 
// in the case of echo "" "" "" "" the output should be three spaces wich are the spaces that get printed in between each argument of the echo command