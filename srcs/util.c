#include "server.h"

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
