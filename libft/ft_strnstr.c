#include "libft.h"

char
	*ft_strnstr(const char *heystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;

	if (!heystack || !needle)
		return (NULL);
	len_needle = ft_strlen(needle);
	if (!len_needle)
		return ((char *)heystack);
	i = 0;
	while (len_needle <= len - i && heystack[i])
	{
		if (!ft_strncmp(heystack + i, needle, len_needle))
			return ((char *)(heystack + i));
		i++;
	}
	return (NULL);
}
