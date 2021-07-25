#include "libft.h"

void
	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*u_s;
	unsigned char	u_c;
	size_t			i;

	if (!s)
		return (NULL);
	u_s = (unsigned char *)s;
	u_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (u_s[i] == u_c)
			return ((void *)(u_s + i));
		i++;
	}
	return (NULL);
}
