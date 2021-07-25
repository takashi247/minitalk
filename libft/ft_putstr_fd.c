#include "libft.h"

void
	ft_putstr_fd(char *s, int fd)
{
	size_t	len_s;

	if (s && 0 <= fd)
	{
		len_s = ft_strlen(s);
		write(fd, s, len_s);
	}
}
