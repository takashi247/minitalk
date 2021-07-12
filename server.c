#include <signal.h>
#include <unistd.h>
#include "server.h"

size_t
    ft_strlen(const char *s)
{
    size_t  len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

static void
    sig_usr(int signo)
{
    if (signo == SIGUSR1)
        write(STDOUT_FILENO, MSG_USR1_SUCCESS, ft_strlen(MSG_USR1_SUCCESS));
    else if (signo == SIGUSR2)
        write(STDOUT_FILENO, MSG_USR2_SUCCESS, ft_strlen(MSG_USR2_SUCCESS));
}

int
    main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        write(STDERR_FILENO, MSG_USR1_FAILURE, ft_strlen(MSG_USR1_FAILURE));
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        write(STDERR_FILENO, MSG_USR2_FAILURE, ft_strlen(MSG_USR2_FAILURE));
    for ( ; ; )
        pause();
}