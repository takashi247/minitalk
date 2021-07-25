#include "libft.h"

int
	ft_atoi(const char *str)
{
	long	l_num;
	int		is_negative;

	l_num = 0;
	is_negative = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_negative = 1;
		str++;
	}
	while (ft_isdigit(*str))
		l_num = l_num * 10 + (*str++ - '0');
	if (is_negative)
		l_num *= -1;
	return ((int)l_num);
}
