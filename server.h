#ifndef SERVER_H
# define SERVER_H

/* required header files */

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define SIGUSR1_CHAR "0"
# define SIGUSR2_CHAR "1"
# define FAILURE 1
# define SUCCESS 0
# define MSG_USR1_FAILURE "can't catch SIGUSR1\n"
# define MSG_USR2_FAILURE "can't catch SIGUSR2\n"

/* global variable for server */

typedef struct s_server
{
	char*   str_bin;
	char*	str;
	int     len_bin;
}   t_server;

#endif
