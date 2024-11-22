#include "minishell.h"

void	env_check(t_env **head, t_env *tmp)
{
	static int	sp[2];
	char		pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", ft_strlen(tmp->key)) == 0)
		{
			if (ft_strncmp(pwd, tmp->value, ft_strlen(tmp->value) + 1))
				tmp->value = ft_strdup_env(pwd);
			sp[1] = 1;
		}
		if (ft_strncmp(tmp->key, "SHLVL", ft_strlen(tmp->key)) == 0)
		{
			shlvl_update(tmp);
			sp[0] = 1;
		}
		tmp = tmp->next;
	}
	shlvl_pwd_env(head, sp, pwd);
}

void	env_stacking(char **env, t_env **env_stack)
{
	int		i;
	int		j;
	int		pos;
	char	*key;

	i = 0;
	while (env[i])
	{
		j = 0;
		pos = equal_sign_position(env[i]);
		while (env[i][j])
			j++;
		key = ft_substr(env[i], 0, pos);
		if (ft_strncmp(key, "OLDPWD", ft_strlen(key)) == 0)
		{
			i++;
			continue ;
		}
		append_node_env(env_stack, key, ft_substr(env[i], pos + 1, j - pos));
		i++;
	}
	env_check(env_stack, *env_stack);
}
