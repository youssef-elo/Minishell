/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:52:17 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/11/25 20:00:06 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_digit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	else
		return (0);
}

int	ft_is_alphanum(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91)
		|| (c > 96 && c < 123) || c == 95)
		return (1);
	else
		return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_strjoinc(const char *s1, const char c)
{
	int		i;
	char	*p;

	if (s1 == NULL && !c)
		return (NULL);
	if (s1 == NULL && c)
		return (ft_chrdup(c));
	if (!c && s1)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	p = gc_handler((i + 2) * sizeof(char), MALLOC);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, (i + 1));
	ft_strchrcat(p, &c, (i + 2));
	return (p);
}
