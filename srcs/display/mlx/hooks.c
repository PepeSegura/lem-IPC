/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:34:57 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/06 16:43:02 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

void close_board(t_display *display)
{
	int	close_display = 0;

	sem_wait(display->sem);
	if (display->shared->players == 0)
		close_display = 1;
	sem_post(display->sem);
	if (display->sem != SEM_FAILED)
		sem_close(display->sem);
	if (close_display == 1)
	{
        int sem_ret = sem_unlink(SEM_NAME);
		if (sem_ret == -1)
		{
        	perror("sem_unlink");
			return ;
		}
		printf("deleting shared memory\n");
		int destroy_ret = destroy_memory_block(FILENAME);
		if (destroy_ret == 1)
			printf("Cannot clear shared memory, close first the display\n");
	}
}

void	close_display(t_display *display)
{
	ft_printf("Escape!\n");
	mlx_terminate(display->mlx);
	if (display->sem != SEM_FAILED)
		sem_close(display->sem);
	exit(0);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	if (!number_in_array(1, (int []){MLX_PRESS}, keydata.action))
		return ;
	if (keydata.key == ESC)
		close_display((t_display *)param);
}
