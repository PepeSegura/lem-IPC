#include "shared_functions.h"

void	ft_perror(char *msg)
{
	dprintf(2, "Error:\n\t");
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	dprintf(2, "Error:\n\t%s\n", str);
	exit(EXIT_FAILURE);
}
