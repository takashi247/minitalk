#include "libft.h"

static int
	count_elems(char const *s, char c)
{
	int	count;
	int	is_delim;

	count = 0;
	while (*s && *s == c)
		s++;
	if (!*s)
		return (count);
	is_delim = 0;
	while (*s)
	{
		if (*s == c && !is_delim)
		{
			count++;
			is_delim = 1;
		}
		else if (*s != c && is_delim)
			is_delim = 0;
		s++;
	}
	if (!is_delim)
		count++;
	return (count);
}

static void
	free_array(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

static char
	**split_str(char const *s, char c, char **array)
{
	char	*head;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		head = (char *)s;
		while (*s != c && *s)
			s++;
		array[i] = ft_substr(head, 0, s - head);
		if (!array[i])
		{
			free_array(&array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

char
	**ft_split(char const *s, char c)
{
	char	**array;
	int		size;

	if (!s)
		return (NULL);
	size = count_elems(s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	return (split_str(s, c, array));
}
