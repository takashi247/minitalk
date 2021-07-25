#include "libft.h"

void
	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*u_dst;
	unsigned char	*u_src;

	if (!dst || !src)
		return (NULL);
	u_dst = (unsigned char *)dst;
	u_src = (unsigned char *)src;
	while (n)
	{
		*u_dst++ = *u_src++;
		n--;
	}
	return (dst);
}
