#include "libft.h"

void
	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	ptr_size;

	ptr_size = count * size;
	ptr = malloc(ptr_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, ptr_size);
	return (ptr);
}
