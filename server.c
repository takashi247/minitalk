#include "server.h"

void
	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

int
	ft_atoi_bin(const char *str)
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
	while (*str == '0' || *str == '1')
		l_num = l_num * 2 + (*str++ - '0');
	if (is_negative)
		l_num *= -1;
	return ((int)l_num);
}

static void
	append_char(char **s, char c)
{
	char	*tmp;
	char	*new_s;

	if (s)
	{
		new_s = (char *)malloc(sizeof(char) * 2);
		if (!new_s)
			exit(FAILURE);
		new_s[0] = c;
		new_s[1] ='\0';
		tmp = *s;
		*s = ft_strjoin(*s, new_s);
		ft_free(&tmp);
		ft_free(&new_s);
		if (!*s)
			exit(FAILURE);
	}
}

static void
	sig_usr(int signo)
{
	static int	len;
	static char	*str_bin;
	static char	*str;
	char		c;

	if (signo == SIGUSR1)
		append_char(&str_bin, CHAR_ZERO);
	else if (signo == SIGUSR2)
		append_char(&str_bin, CHAR_ONE);
	len++;
	if (len == 8)
	{
		c = (char)ft_atoi_bin(str_bin);
		append_char(&str, c);
		if (!c)
		{
			ft_putendl_fd(str, STDOUT_FILENO);
			ft_free(&str);
		}
		ft_free(&str_bin);
		len = 0;
	}
}

int
	main(void)
{
	const int	server_pid = getpid();
	const char	*pid_str = ft_itoa(server_pid);

	write(STDOUT_FILENO, pid_str, ft_strlen(pid_str));
	write(STDOUT_FILENO, "\n", 1);
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		write(STDERR_FILENO, MSG_USR1_FAILURE, ft_strlen(MSG_USR1_FAILURE));
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		write(STDERR_FILENO, MSG_USR2_FAILURE, ft_strlen(MSG_USR2_FAILURE));
	while (1)
		pause();
}
