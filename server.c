#include "server.h"

static void
	safe_free(unsigned char **s)
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
	append_char(unsigned char **s, unsigned char c)
{
	unsigned char	*tmp;
	unsigned char	*new_s;

	if (s)
	{
		new_s = (unsigned char *)malloc(sizeof(unsigned char) * 2);
		if (!new_s)
			exit(FAILURE);
		new_s[0] = c;
		new_s[1] ='\0';
		tmp = *s;
		*s = (unsigned char *)ft_strjoin((char *)*s, (char *)new_s);
		safe_free(&tmp);
		safe_free(&new_s);
		if (!*s)
			exit(FAILURE);
	}
}

static void
	sig_usr(int signo, siginfo_t *siginfo, void *context)
{
	static volatile int		len;
	static unsigned char	*str_bin;
	static unsigned char	*str;
	unsigned char			c;
	const pid_t				client_pid = siginfo->si_pid;

	if (signo == SIGUSR1)
		append_char(&str_bin, (unsigned char)CHAR_ZERO);
	else if (signo == SIGUSR2)
		append_char(&str_bin, (unsigned char)CHAR_ONE);
	kill(client_pid, SIGUSR1);
	len++;
	if (len == 8)
	{
		c = (unsigned char)ft_atoi_bin((char *)str_bin);
		append_char(&str, c);
		if (!c)
		{
			ft_putendl_fd((char *)str, STDOUT_FILENO);
			safe_free(&str);
			kill(client_pid, SIGUSR2);
		}
		safe_free(&str_bin);
		len = 0;
	}
}

int
	main(void)
{
	char				*pid_str;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = sig_usr;
	sa.sa_flags |= SA_RESTART;
	sa.sa_flags |= SA_SIGINFO;
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		exit(FAILURE);
	write(STDOUT_FILENO, pid_str, ft_strlen(pid_str));
	write(STDOUT_FILENO, "\n", 1);
	safe_free((unsigned char **)&pid_str);
	if (sigaction(SIGUSR1, &sa, NULL))
	{
		ft_putendl_fd(MSG_USR1_FAILURE, STDERR_FILENO);
		exit(FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL))
	{
		ft_putendl_fd(MSG_USR2_FAILURE, STDERR_FILENO);
		exit(FAILURE);
	}
	while (1)
		pause();
}
