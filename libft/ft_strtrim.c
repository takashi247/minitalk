#include "libft.h"
#include <stdio.h>

static void
	update_start_end(char const *s, char const *set, size_t *start, size_t *end)
{
	const char	*head;

	head = set;
	while (*set && *start < *end)
	{
		if (s[*start] == *set)
		{
			(*start)++;
			set = head;
		}
		else
			set++;
	}
	set = head;
	while (*set && *start < *end)
	{
		if (s[(*end) - 1] == *set)
		{
			(*end)--;
			set = head;
		}
		else
			set++;
	}
}

char
	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;
	char	*head;

	if (!s1 || !set)
		return (NULL);
	if (!*s1 || !*set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	update_start_end(s1, set, &start, &end);
	if (end <= start)
		return (ft_strdup("\0"));
	trimmed = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trimmed)
		return (NULL);
	head = trimmed;
	while (start < end)
		*trimmed++ = *(s1 + start++);
	*trimmed = '\0';
	return (head);
}
