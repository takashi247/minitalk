#include "libft.h"

size_t
	ft_strlen_u(const unsigned char *us)
{
	size_t	len;

	len = 0;
	while (us[len])
		len++;
	return (len);
}
