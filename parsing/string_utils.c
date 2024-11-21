#include "../minishell.h"

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

	if (len == 0)
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
