#ifndef SERVER_H
# define SERVER_H

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
# define MSG_EMPTYSET_FAILURE "can't initialize a signal set\n"
# define MSG_ADDSET_FAILURE "can't add a signal to the set\n"
# define FLAG_NOSIG 0
# define FLAG_SIGUSR1 1
# define FLAG_SIGUSR2 2

#endif
