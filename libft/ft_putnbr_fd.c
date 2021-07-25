#include "libft.h"

static int
	calc_digits(long long_n)
{
	long	digits;

	digits = 1;
	if (long_n == 0)
		return (digits);
	while (long_n)
	{
		long_n /= 10;
		digits *= 10;
	}
	digits /= 10;
	return (digits);
}

void
	ft_putnbr_fd(int n, int fd)
{
	long	long_n;
	long	digits;
	char	c;

	if (0 <= fd)
	{
		long_n = (long)n;
		if (long_n < 0)
		{
			ft_putchar_fd('-', fd);
			long_n *= -1;
		}
		digits = calc_digits(long_n);
		while (digits)
		{
			c = long_n / digits + '0';
			ft_putchar_fd(c, fd);
			long_n %= digits;
			digits /= 10;
		}
	}
}
