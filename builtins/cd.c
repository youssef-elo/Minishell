#include "../minishell.h"

void env_update(t_env *head, char *key, char *value)
{
	while(head)
	{
		if (ft_strncmp(key, head->key, ft_strlen(head->key) + 1) == 0)
		{
			head->value = ft_strdup_env(value);
			return ;
		}
		head = head->next;
	}
}

void	export_env_update(t_export *exp, t_exec *prompt,char *key, char *value)
{
	int f;

	f = 0;
	while(exp)
	{
		if (ft_strncmp(key, exp->key, ft_strlen(exp->key) + 1) == 0)
		{
			exp->value = ft_strdup_env(value);
			f = 1;
			break ;
		}
		exp = exp->next;
	}
	if (f == 1)
	{
		update_append_env(prompt->head, 1, key, value);
	}
}

int cd_home(t_exec *prompt, t_export **head, char *cwd)
{
	char	*newdir;
	char	*pwd;

	newdir = ft_getenv(prompt->env, "HOME");
	if (!newdir)
	{
		ft_putstrnl_fd("cd : HOME not set", 2);
		return (1);
	}
	if (chdir(newdir) == -1)
	{
		ft_putstr_fd("cd : ", 2);
		perror(newdir);
		return (1);
	}
	pwd = ft_getenv(prompt->env, "PWD");
	if (!pwd)
		pwd = cwd;
	export_env_update(*head, prompt, "OLDPWD", pwd);
	export_env_update(*head, prompt, "PWD", newdir);
	return (0);
}

int cd_path(t_exec *prompt, t_export **head, char *cwd)
{
	char *pwd;

	if (chdir(prompt->args[1]) == -1)
	{
		ft_putstr_fd("cd : ", 2);
		perror(prompt->args[1]);
		return (1);
	}
	pwd = ft_getenv(prompt->env, "PWD");
	if (!pwd)
		pwd = cwd;
	export_env_update(*head, prompt, "OLDPWD", pwd);
	export_env_update(*head, prompt, "PWD", prompt->args[1]);
	return (0);
}

void getcwd_fail(t_exec *prompt, t_export **head)

int	ft_cd(t_exec *prompt, t_export **head)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	char	*error;

	getcwd(cwd, PATH_MAX);
	if (!prompt->args[1])
		return (cd_home(prompt, head, cwd));
	if (chdir(prompt->args[1]) == -1)
	{
		ft_putstr_fd("cd : ", 2);
		perror(prompt->args[1]);
		return (1);
	}
	pwd = ft_getenv(prompt->env, "PWD");
	if (!pwd)
		pwd = cwd;
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("cd: error retrieving current directory");
		export_env_update(*head, prompt, "OLDPWD", pwd);
		error = ft_getenv(prompt->env, "PWD");
		if (error[ft_strlen(error) - 1] != '/')
			error = ft_strjoin(error, "/");
		export_env_update(*head, prompt, "PWD", ft_strjoin(error, prompt->args[1]));
		return (0);
	}
	export_env_update(*head, prompt, "OLDPWD", pwd);
	export_env_update(*head, prompt, "PWD", cwd);
	return (0);
}

/*
	the PWD and OLDPWD can only be updated the bash doesnt not create them if they dont exist ,
	when you first run bash there is already the pwd but the OLDPWD is exported but with no value
	thus why it doesnt show in the env if you cd the oldpwd will get a value and be shown in the env ,
	if you were to unset it before using cd then OLDPWD will not be available , since shell will only update it if found not create it .

	in bash the PWD and OLDPWD is updated as follows when using cd the value of PWD is put in the OLDPWD (from env)
	if the value of PWD is nothing then nothing is put in the OLDPWD 
	bash also usese its local variables so in case you unset PWD and then you use cd the value of OLDPWD will become blank
	since the local varible was still empty but after it the variable is updated to the pwd, so in the next cd OLDPWD will have the correct OLDPWD
*/