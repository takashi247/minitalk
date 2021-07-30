#include "server.h"

static volatile	sig_atomic_t
	g_server_flag;

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
		g_server_flag = FLAG_SIGUSR1;
		consecutive_zeros++;
	}
	else if (signo == SIGUSR2)
	{
		g_server_flag = FLAG_SIGUSR2;
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
	static volatile sig_atomic_t	bit_shifter;
	static volatile unsigned char	*str_u;
	static volatile unsigned char	uc;

	while (g_server_flag == FLAG_NOSIG)
		usleep(1);
	if (g_server_flag == FLAG_SIGUSR1)
		uc &= ~(1 << bit_shifter);
	else if (g_server_flag == FLAG_SIGUSR2)
		uc |= (1 << bit_shifter);
	bit_shifter++;
	if (bit_shifter == 8)
	{
		append_char_u((unsigned char **)&str_u, uc);
		if (!uc)
		{
			ft_putendl_fd_u((unsigned char *)str_u, STDOUT_FILENO);
			ft_free_str_u((unsigned char **)&str_u);
		}
		bit_shifter = 0;
	}
	g_server_flag = FLAG_NOSIG;
}

int
	main(void)
{
	char				*pid_str;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = sig_usr;
	sa.sa_flags |= SA_RESTART;
	sa.sa_flags |= SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL))
		exit_with_error_msg(MSG_USR1_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL))
		exit_with_error_msg(MSG_USR2_FAILURE);
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		exit(FAILURE);
	ft_putstr_fd("[Server PID]: ", STDOUT_FILENO);
	ft_putendl_fd(pid_str, STDOUT_FILENO);
	ft_free_str(&pid_str);
	while (1)
		run_server();
	return (SUCCESS);
}
