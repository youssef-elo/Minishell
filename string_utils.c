/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 06:12:17 by hrochd            #+#    #+#             */
/*   Updated: 2024/09/22 23:43:39 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	slen;
	char	*s2;

	i = 0;
	slen = ft_strlen(s1) + 1;
	s2 = malloc(slen * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, slen);
	return (s2);
}

char	*ft_chrdup(const char s1)
{
	size_t	i;
	size_t	slen;
	char	*s2;

	i = 0;
	slen = 1;
	s2 = malloc(slen * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, &s1, slen);
	return (s2);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	char	*p;

	if (s == NULL)
		return (NULL);
	i = (size_t)start;
	j = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - i)
		len = slen - i;
	p = (char *)malloc(len + 1);
	if (p == NULL)
		return (NULL);
	while (j < len && s[i])
		p[j++] = s[i++];
	p[j] = '\0';
	return (p);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (slen);
	dlen = ft_strlen(dst);
	if (dlen >= dstsize)
		return (slen + dstsize);
	if (dlen < dstsize)
		ft_strlcpy(dst + dlen, src, dstsize - dlen);
	return (dlen + slen);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2)
		return (ft_strdup(s2));
	if (s2 == NULL && s1)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = malloc((i + j + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, (i + 1));
	ft_strlcat(p, s2, (i + j + 1));
	return (p);
}
// char	*ft_strjoinc(const char **s1, const char c)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*p;

// 	if (s1 == NULL && !c)
// 		return (NULL);
// 	if (s1 == NULL && c)
// 		return (ft_chrdup(c));
// 	if (!c && s1)
// 		return (ft_strdup(&s1));
// 	i = ft_strlen(s1);
// 	j = 1;
// 	p = malloc((i + 2) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	ft_strlcpy(p, s1, (i + 1));
// 	ft_strlcat(p, &c, (i + 2));
// 	return (p);
// }

