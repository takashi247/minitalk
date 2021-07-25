#include "libft.h"

void
	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*u_dst;
	const unsigned char	*u_src = (unsigned char *)src;
	size_t				i;

	if (!dst || !src)
		return (NULL);
	u_dst = (unsigned char *)dst;
	i = 0;
	if (u_dst < u_src)
	{
		while (i < len)
		{
			u_dst[i] = u_src[i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			u_dst[len - i - 1] = u_src[len - i - 1];
			i++;
		}
	}
	return (dst);
}
