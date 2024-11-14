#include "minishell.h"

int	equal_sign_position(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	alnm(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	shlvl_pwd_env(t_env **head, int sp[], char *pwd)
{
	if (!sp[0])
		append_node_env(head, "SHLVL", "1");
	if (!sp[1])
		append_node_env(head, "PWD", pwd);
}

long long	shlvl_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (ft_is_digit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		if (res > LLONG_MAX && sign == 1)
			return (2147463648);
		else if (res > (unsigned long long)LLONG_MAX + 1)
			return (2147463648);
		i++;
	}
	return ((long long)res * sign);
}

void	shlvl_update(t_env *tmp)
{
	long long	next;

	next = shlvl_atoi(tmp->value) + 1;
	if (tmp->value[0] == '-' && alnm(tmp->value + 1))
		tmp->value = ft_strdup_env("0");
	if (!alnm(tmp->value))
		tmp->value = ft_strdup_env("1");
	if ((*(tmp->value) == '+' && alnm(tmp->value + 1)) || alnm(tmp->value))
	{
		if (ft_strlen(tmp->value) > 12 || next > 2147483647)
			tmp->value = ft_strdup_env("0");
		else if (next - 1 >= 1000)
		{
			ft_putstr_fd("minishell: warning: shell level (", 2);
			ft_putstr_fd(ft_itoa(next), 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
			tmp->value = ft_strdup_env("1");
		}
		else if (next > 1000)
			tmp->value = ft_strdup_env("1");
		else if (next < 1000)
			tmp->value = ft_strdup_env(ft_itoa((int)next));
		else if (next == 1000)
			tmp->value = ft_strdup_env("");
	}
}

// void	env_check(t_env **head, t_env *tmp)
// {
// 	static int	sp[2];
// 	char		pwd[PATH_MAX];

// 	getcwd(pwd, PATH_MAX);
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->key, "PWD", ft_strlen(tmp->key)) == 0)
// 		{
// 			if (ft_strncmp(pwd, tmp->value, ft_strlen(tmp->value) + 1))
// 				tmp->value = ft_strdup_env(pwd);
// 			sp[1] = 1;
// 		}
// 		if (ft_strncmp(tmp->key, "SHLVL", ft_strlen(tmp->key)) == 0)
// 		{
// 			shlvl_update(tmp, sp);
// 			sp[0] = 1;
// 		}
// 		tmp = tmp->next;
// 	}
// 	shlvl_pwd_env(head, sp, pwd);
// }

// void	env_stacking(char **env, t_env **env_stack)
// {
// 	int		i;
// 	int		j;
// 	int		pos;
// 	char	*key;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		pos = equal_sign_position(env[i]);
// 		while (env[i][j])
// 			j++;
// 		key = ft_substr(env[i], 0, pos);
// 		if (ft_strncmp(key, "OLDPWD", ft_strlen(key)) == 0)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		append_node_env(env_stack, key, ft_substr(env[i], pos + 1, j - pos));
// 		i++;
// 	}
// 	env_check(env_stack, *env_stack);
// }
