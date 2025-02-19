#include "DISPLAY.h"

void	ft_perror(char *msg)
{
	ft_dprintf(2, "Error:\n\t");
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	ft_dprintf(2, "Error:\n\t%s\n", str);
	exit(EXIT_FAILURE);
}

void	ft_mlx_error(void)
{
	ft_dprintf(2, "%s", mlx_strerror(mlx_errno));
}
