/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:00:26 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 13:00:27 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

void	*close_board(t_display *display)
{
	if (display->sem != SEM_FAILED)
		sem_close(display->sem);
	exit(0);
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
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_display((t_display *)param);
}
