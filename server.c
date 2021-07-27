#include "server.h"

static volatile	char
	*g_server;

void
	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

static void
	add_binary_str(char *s)
{
	char	*tmp;

	if (s)
	{
		if (!g_server)
			g_server = ft_strdup(s);
		else
		{
			tmp = (char *)g_server;
			g_server = ft_strjoin((const char *)g_server, s);
			ft_free(&tmp);
		}
	}
}

static void
	sig_usr(int signo)
{
	size_t	len;

	if (signo == SIGUSR1)
		add_binary_str(SIGUSR1_CHAR);
	else if (signo == SIGUSR2)
		add_binary_str(SIGUSR2_CHAR);
	if (!g_server)
		exit(FAILURE);
	len = ft_strlen((const char *)g_server);
	if (len == 8)
	{
		ft_putstr_fd((char *)g_server, STDOUT_FILENO);
		ft_free((char **)(&g_server));
	}
}

int
	main(void)
{
	const int	server_pid = getpid();
	const char	*pid_str = ft_itoa(server_pid);

	write(STDOUT_FILENO, pid_str, ft_strlen(pid_str));
	write(STDOUT_FILENO, "\n", 1);
	g_server = NULL;
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		write(STDERR_FILENO, MSG_USR1_FAILURE, ft_strlen(MSG_USR1_FAILURE));
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		write(STDERR_FILENO, MSG_USR2_FAILURE, ft_strlen(MSG_USR2_FAILURE));
	while (1)
		pause();
}
