#include "minishell.h"

int equal_sign_position(char *var)
{
	int i;

	i = 0;
	while(var[i])
	{
		if(var[i] == '=')
			break;
		i++;
	}
	return (i);
}

int ft_isallnum(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void shlvl_pwd_env(t_env **head, int sp[], char *pwd)
{
	if (!sp[0])
		append_node_env(head, "SHLVL", "1");
	if (!sp[1])
		append_node_env(head, "PWD", pwd);
}


void env_check(t_env **head, t_env *tmp)
{
	static int	sp[2];
	char		pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	while(tmp)
	{
		if(ft_strncmp(tmp->key, "PWD", ft_strlen(tmp->key)) == 0)
		{
			if (ft_strncmp(pwd, tmp->value, ft_strlen(tmp->value) + 1))
				tmp->value = ft_strdup_env(pwd);
			sp[1] = 1;
		}
		if(ft_strncmp(tmp->key, "SHLVL", ft_strlen(tmp->key)) == 0)
		{
			if (!ft_isallnum(tmp->value))
				tmp->value = ft_strdup_env("1");
			else
				tmp->value = ft_strdup_env(ft_itoa(ft_atoi(tmp->value) + 1));
			sp[0] = 1;
		}
		tmp = tmp->next;
	}
	shlvl_pwd_env(head, sp, pwd);
}

// SHLVLV should be incremented by 1 or reset to 1 if it has non numerical value or if it doesnt exist
void env_stacking(char **env, t_env **env_stack)
{
	int i;
	int j;
	int equal_pos;
	char *key;

	i = 0;
	while(env[i])
	{
		j = 0;
		equal_pos = equal_sign_position(env[i]);
		while(env[i][j])
			j++;
		key = ft_substr(env[i], 0, equal_pos);
		if (ft_strncmp(key, "OLDPWD", ft_strlen(key)) == 0)
		{
			i++;
			continue ;
		}
		append_node_env(env_stack, key, ft_substr(env[i], equal_pos + 1, j - equal_pos));
		i++;
	}
	env_check(env_stack, *env_stack);
}
