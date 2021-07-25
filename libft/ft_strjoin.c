#include "libft.h"

char
	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_joined;
	char	*s_joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_joined = ft_strlen(s1) + ft_strlen(s2);
	s_joined = (char *)malloc(sizeof(char) * (len_joined + 1));
	if (!s_joined)
		return (NULL);
	ft_strlcpy(s_joined, s1, len_joined + 1);
	ft_strlcat(s_joined, s2, len_joined + 1);
	return (s_joined);
}
