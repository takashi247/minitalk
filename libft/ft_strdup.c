#include "libft.h"

char
	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*head;

	if (!s1)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	head = dup;
	while (*s1)
		*dup++ = *s1++;
	*dup = '\0';
	return (head);
}
