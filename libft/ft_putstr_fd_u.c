#include "libft.h"

void
	ft_putstr_fd_u(unsigned char *us, int fd)
{
	size_t	len_us;

	if (us && 0 <= fd)
	{
		len_us = ft_strlen_u(us);
		write(fd, us, len_us);
	}
}
