#include "../minishell.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	slen;

	i = 0;
	if (dstsize == 2)
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
	int		i;
	int		slen;
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
