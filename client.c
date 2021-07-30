#include "client.h"

static volatile sig_atomic_t
	client_flag;

static void
	send_signal(pid_t server_pid, unsigned char uc)
{
	int	bit_shifter;

	if (kill(server_pid, 0))
	{
		ft_putendl_fd(MSG_SERVER_PID_ERROR, STDERR_FILENO);
		exit(FAILURE);
	}
	bit_shifter = 7;
	while (0 <= bit_shifter)
	{
		if ((uc >> bit_shifter) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
		bit_shifter--;
	}
}

static void
	sig_usr(int signo)
{
	(void)signo;
	ft_putendl_fd(MSG_RECEIVE_ACKNOWLEDGEMENT, STDOUT_FILENO);
	client_flag = 1;
}

int
	main(int ac, char **av)
{
	pid_t				server_pid;
	unsigned char		*str_u;

	if (ac != 3)
	{
		ft_putendl_fd(MSG_USAGE_ERROR, STDERR_FILENO);
		return (FAILURE);
	}
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		ft_putendl_fd(MSG_USR1_FAILURE, STDERR_FILENO);
		exit(FAILURE);
	}
	client_flag = 0;
	server_pid = (pid_t)ft_atoi(av[1]);
	str_u = (unsigned char *)av[2];
	while (*str_u)
	{
		send_signal(server_pid, *str_u);
		str_u++;
	}
	send_signal(server_pid, *str_u);
	while (!client_flag)
		usleep(100);
	return (SUCCESS);
}
