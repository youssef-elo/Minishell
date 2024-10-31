#include "../minishell.h"

// int	ft_cd(t_exec *data)
// {
// 	if (chdir("Desktop"))
// 		perror;
// }

int main(int argc , char *argv[]){
	if (chdir(argv[1]) == -1 )
		perror("cd :");
	printf("%s\n", getcwd(NULL, 0));
}
/*
	the PWD and OLDPWD can only be set the bash doesnt not create them if they dont exist ,
	when you first run bash there is already the pwd but the OLDPWD is exported but with no value
	thus why it doesnt show in the env if you cd the oldpwd will get a value and be shown in the env ,
	if you were to unset it before using cd then OLDPWD will not be available , since shell will only update it if found not create it .

	in bash the PWD and OLDPWD is updated as follows when using cd the value of PWD is put in the OLDPWD (from env)
	if the value of PWD is nothing then nothing is put in the OLDPWD 
	bash also usese its local variables so in case you unset PWD and then you use cd the value of OLDPWD will become blank
	 since the local varible was still empty but after it the variable is updated to the pwd, so in the next cd OLDPWD will have the correct OLDPWD
*/