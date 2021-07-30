#ifndef CLIENT_H
# define CLIENT_H

/* required header files */

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define FAILURE 1
# define SUCCESS 0
# define MSG_USR1_FAILURE "can't catch SIGUSR1\n"
# define MSG_USAGE_ERROR "Bad usage. Specify a server PID and string"
# define MSG_SERVER_PID_ERROR "Error: server pid is invalid"
# define MSG_RECEIVE_ACKNOWLEDGEMENT "Success: receive acknowledgement"
# define BUFFER_TIME 100
# define MAX_BIT 8

#endif
