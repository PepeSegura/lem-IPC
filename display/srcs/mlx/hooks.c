/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:34:57 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/05 21:04:33 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

void	close_display(t_display *display)
{
	ft_printf("Escape!\n");
	mlx_terminate(display->mlx);
	exit(0);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_display		*display;

	display = (t_display *)param;
	if (!number_in_array(2, (int []){MLX_PRESS, MLX_REPEAT}, keydata.action))
		return ;
	if (keydata.key == ESC)
		close_display(display);
	// draw_map(display);
}
