#include "GAME.h"

void	close_player(t_game *player)
{
	ft_printf("Escape!\n");
	mlx_terminate(player->mlx);
	if (player->sem != SEM_FAILED)
		sem_close(player->sem);
	exit(0);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	if (!number_in_array(1, (int []){MLX_PRESS}, keydata.action))
		return ;
	if (keydata.key == ESC)
		close_player((t_game *)param);
}