#include "../minishell.h"

void	export_env_update(t_export *exp, t_exec *prompt, char *key, char *value)
{
	int	f;

	f = 0;
	while (exp)
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

int	cd_home(t_exec *prompt, t_export **head, char *cwd)
{
	char	*newdir;
	char	*pwd;

	newdir = ft_getenv(prompt->env, "HOME");
	if (!newdir)
	{
		ft_putstr_fd("cd : HOME not set\n", 2);
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

int	cd_path(t_exec *prompt, t_export **head, char *cwd)
{
	char	*pwd;

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

int	ft_cd(t_exec *prompt, t_export **head)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	getcwd(cwd, PATH_MAX);
	if (!prompt->args[1])
		return (cd_home(prompt, head, cwd));
	if (!prompt->args[1][0])
		return (0);
	if (chdir(prompt->args[1]) == -1)
	{
		ft_putstr_fd("cd : ", 2);
		perror(prompt->args[1]);
		return (1);
	}
	pwd = ft_getenv(prompt->env, "PWD");
	if (!pwd)
		pwd = cwd;
	export_env_update(*head, prompt, "OLDPWD", cwd);
	if (getcwd(cwd, PATH_MAX) == NULL)
		perror("cd: error retrieving current directory");
	export_env_update(*head, prompt, "PWD", cwd);
	return (0);
}
