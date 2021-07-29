#include "server.h"

static volatile sig_atomic_t
	server_flag;

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
	static volatile sig_atomic_t	len;
	static volatile sig_atomic_t	consecutive_zeros;
	const pid_t						client_pid = siginfo->si_pid;

	(void)context;
	if (signo == SIGUSR1)
	{
		server_flag = 1;
		consecutive_zeros++;
	}
	else if (signo == SIGUSR2)
	{
		server_flag = 2;
		if (consecutive_zeros)
			consecutive_zeros = 0;
	}
	len++;
	if (len == 8)
	{
		if (consecutive_zeros == 8)
			kill(client_pid, SIGUSR1);
		len = 0;
		consecutive_zeros = 0;
	}
}

static void
	exit_with_error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(FAILURE);
}

static void
	run_server(void)
{
	static volatile char			*str_bin;
	static volatile unsigned char	*str;
	volatile unsigned char			c;

	while (server_flag == 0)
		usleep(1);
	if (server_flag == 1)
		append_char((char **)&str_bin, CHAR_ZERO);
	else if (server_flag == 2)
		append_char((char **)&str_bin, CHAR_ONE);
	if (ft_strlen((char *)str_bin) == 8)
	{
		c = (unsigned char)ft_atoi_bin((char *)str_bin);
		append_char_u((unsigned char **)&str, c);
		if (!c)
		{
			ft_putendl_fd_u((unsigned char *)str, STDOUT_FILENO);
			ft_free_str_u((unsigned char **)&str);
		}
		ft_free_str((char **)&str_bin);
	}
	server_flag = 0;
}

int
	main(void)
{
	char				*pid_str;
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) != 0)
		exit_with_error_msg(MSG_EMPTYSET_FAILURE);
	if (sigaddset(&sa.sa_mask, SIGUSR1) != 0
		|| sigaddset(&sa.sa_mask, SIGUSR2) != 0)
		exit_with_error_msg(MSG_ADDSET_FAILURE);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = sig_usr;
	sa.sa_flags |= SA_RESTART;
	sa.sa_flags |= SA_SIGINFO;
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		exit(FAILURE);
	ft_putstr_fd("[Server PID]: ", STDOUT_FILENO);
	ft_putendl_fd(pid_str, STDOUT_FILENO);
	ft_free_str(&pid_str);
	if (sigaction(SIGUSR1, &sa, NULL))
		exit_with_error_msg(MSG_USR1_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL))
		exit_with_error_msg(MSG_USR2_FAILURE);
	while (1)
		run_server();
	return (SUCCESS);
}
