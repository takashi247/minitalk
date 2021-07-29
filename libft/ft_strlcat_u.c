#include "libft.h"

size_t
	ft_strlcat_u(unsigned char *dst, const unsigned char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	if (!src || !dst)
		return (0);
	len_src = ft_strlen_u(src);
	len_dst = ft_strlen_u(dst);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	i = 0;
	while (src[i] && i < dstsize - len_dst - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_src + len_dst);
}
