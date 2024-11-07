#include "minishell.h"

int	ft_isspace(int c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

int	ft_sign(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long		r;
	long		check;

	i = 0;
	sign = 1;
	r = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (ft_is_digit(str[i]) == 1)
	{
		check = r * 10 + (str[i] - 48);
		if (check < r)
			return (ft_sign(sign));
		r *= 10;
		r += (str[i] - 48);
		i++;
	}
	return ((int)(r * sign));
}

long long exit_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign =1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while(ft_is_digit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		if (res > LLONG_MAX && sign == 1)
			return (255);
		else if (res > (unsigned long long)LLONG_MAX + 1)
			return (255);
		i++;
	}
	return ((long long)res * sign);
}