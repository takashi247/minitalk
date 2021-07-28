#ifndef CLIENT_H
# define CLIENT_H

/* required header files */

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define CHAR_ZERO '0'
# define CHAR_ONE '1'
# define FAILURE 1
# define SUCCESS 0
# define MSG_USR1_FAILURE "can't catch SIGUSR1\n"
# define MSG_USR2_FAILURE "can't catch SIGUSR2\n"
# define MSG_USAGE_ERROR "Bad usage. Specify a server PID and string"
# define MSG_BIN_STR_ERROR "Error: only 0 and 1 are allowed to use"
# define MSG_SERVER_PID_ERROR "Error: server pid is not correct"
# define MSG_RECEIVE_ACKNOWLEDGEMENT "Success: receive acknowledgement"
# define STR_BIN_NULL "00000000"

#endif
