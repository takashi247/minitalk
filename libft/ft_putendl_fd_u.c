#include "libft.h"

void
	ft_putendl_fd_u(unsigned char *us, int fd)
{
	if (us && 0 <= fd)
	{
		ft_putstr_fd_u(us, fd);
		ft_putchar_fd('\n', fd);
	}
}
