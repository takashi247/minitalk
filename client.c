#include "client.h"

static volatile int
	client_flag;

static void
	safe_free(unsigned char **s)
{
	free(*s);
	*s = NULL;
}

static unsigned char
	*convert_to_bin(char c)
{
	unsigned char	*str_bin;
	int				i;
	unsigned char	divider;
	unsigned char	uc;

	uc = (unsigned char)c;
	str_bin = (unsigned char *)malloc(sizeof(unsigned char) * 9);
	if (!str_bin)
		return (NULL);
	divider = 2 * 2 * 2 * 2 * 2 * 2 * 2;
	i = 0;
	while (i < 8)
	{
		str_bin[i] = uc / divider + '0';
		uc %= divider;
		divider /= 2;
		i++;
	}
	str_bin[i] = '\0';
	return (str_bin);
}

static void
	send_signal(pid_t server_pid, unsigned char *str_bin)
{
	if (!kill(server_pid, 0))
	{
		while (*str_bin)
		{
			if (*str_bin == (unsigned char)CHAR_ZERO)
			{
				kill(server_pid, SIGUSR1);
				while (!client_flag)
					pause();
				client_flag = 0;
			}
			else if (*str_bin == (unsigned char)CHAR_ONE)
			{
				kill(server_pid, SIGUSR2);
				while (!client_flag)
					pause();
				client_flag = 0;
			}
			else
			{
				ft_putendl_fd(MSG_BIN_STR_ERROR, STDERR_FILENO);
				break ;
			}
			str_bin++;
		}
	}
	else
		ft_putendl_fd(MSG_SERVER_PID_ERROR, STDERR_FILENO);
}

static void
	sig_usr(int signo)
{
	if (signo == SIGUSR1)
		client_flag = 1;
	else if (signo == SIGUSR2)
	{
		ft_putendl_fd(MSG_RECEIVE_ACKNOWLEDGEMENT, STDOUT_FILENO);
		client_flag = 1;
	}
}

int
	main(int ac, char **av)
{
	pid_t				server_pid;
	unsigned char		*str_bin;
	struct sigaction	sa;

	if (ac != 3)
	{
		ft_putendl_fd(MSG_USAGE_ERROR, STDERR_FILENO);
		return (FAILURE);
	}
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sig_usr;
	sa.sa_flags |= SA_RESTART;
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
	client_flag = 0;
	server_pid = (pid_t)ft_atoi(av[1]);
	while (*av[2])
	{
		str_bin = convert_to_bin(*av[2]);
		if (!str_bin)
			return (FAILURE);
		send_signal(server_pid, str_bin);
		safe_free(&str_bin);
		av[2]++;
	}
	send_signal(server_pid, (unsigned char *)STR_BIN_NULL);
	while (!client_flag)
		pause();
	return (SUCCESS);
}
