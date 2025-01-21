/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:34:57 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/21 19:39:29 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

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
