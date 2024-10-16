#include "../minishell.h"

char *ft_getenv(t_env *envi , char *key)
{
	while(envi)
	{
		if (ft_strncmp(key, envi->key, ft_strlen(key) + 1) == 0)
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}

void ft_pwd(t_exec *data)
{
	char dir[PATH_MAX];
	char *env_pwd;

	getcwd(dir, PATH_MAX);
	if(dir[0] == '/')
	{
		ft_putstrnl_fd(dir , 1);
		return ;
	}
	else
	{
		env_pwd = ft_getenv(data->env, "PWD");
		if (env_pwd)
		{
			ft_putstrnl_fd(env_pwd , data->fd_out);
		}
	}
	if (!env_pwd)
		ft_putstrnl_fd("pwd : error retreiving current directory", 2);
}
