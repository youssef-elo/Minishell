#include "minishell.h"

int	ft_is_digit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	else
		return (0);
}
int	ft_is_alphanum(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123) || c == 95)
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

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	slen;

	i = 0;
	if(dstsize == 2)
		slen = 2;
	else
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
	int	i;
	int	slen;
	char	*s2;

	i = 0;
	if (!s1)
		return (NULL);
	slen = ft_strlen(s1) + 1;
	s2 = gc_handler(slen * sizeof(char), MALLOC);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, slen);
	return (s2);
}

char	*ft_chrdup(const char c)
{
	char	*s;

	s = gc_handler(2 * sizeof(char), MALLOC);
	if (!s)
		return (NULL);
	ft_strlcpy(s, &c, 2);
	return (s);
}

char	*ft_substr(const char *s, int start, int len)
{
	int		i;
	int		j;
	int		slen;
	char	*p;

	if(len == 0)
		return (ft_strdup(""));
	if (s == NULL)
		return (NULL);
	i = (int)start;
	j = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - i)
		len = slen - i;
	p = (char *)gc_handler(len + 1, MALLOC);
	if (p == NULL)
		return (NULL);
	while (j < len && s[i])
		p[j++] = s[i++];
	p[j] = '\0';
	return (p);
}

int	ft_strlcat(char *dst, const char *src, int dstsize)
{
	int	dlen;
	int	slen;

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

int	ft_strchrcat(char *dst, const char *src, int dstsize)
{
	int	dlen;
	int	slen;

	slen = 1;
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
	int		i;
	int		j;
	char	*p;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2)
		return (ft_strdup(s2));
	if (s2 == NULL && s1)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = gc_handler((i + j + 1) * sizeof(char), MALLOC);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, (i + 1));
	ft_strlcat(p, s2, (i + j + 1));
	return (p);
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


