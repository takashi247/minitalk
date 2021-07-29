#include "server.h"

void
	ft_free_str(char **s)
{
	free(*s);
	*s = NULL;
}

void
	ft_free_str_u(unsigned char **us)
{
	free(*us);
	*us = NULL;
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
		ft_free_str(&tmp);
		ft_free_str(&new_s);
		if (!*s)
			exit(FAILURE);
	}
}

static void
	append_char_u(unsigned char **s, unsigned char c)
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
		*s = ft_strjoin_u(*s, new_s);
		ft_free_str_u(&tmp);
		ft_free_str_u(&new_s);
		if (!*s)
			exit(FAILURE);
	}
}

static void
	sig_usr(int signo, siginfo_t *siginfo, void *context)
{
	static volatile int		len;
	static char				*str_bin;
	static unsigned char	*str;
	unsigned char			c;
	const pid_t				client_pid = siginfo->si_pid;

	(void)context;
	if (signo == SIGUSR1)
		append_char(&str_bin, CHAR_ZERO);
	else if (signo == SIGUSR2)
		append_char(&str_bin, CHAR_ONE);
	kill(client_pid, SIGUSR1);
	len++;
	if (len == 8)
	{
		c = (unsigned char)ft_atoi_bin(str_bin);
		append_char_u(&str, c);
		if (!c)
		{
			ft_putendl_fd_u(str, STDOUT_FILENO);
			ft_free_str_u(&str);
			kill(client_pid, SIGUSR2);
		}
		ft_free_str(&str_bin);
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
	ft_free_str(&pid_str);
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
