/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:34:57 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/15 12:52:43 by psegura-         ###   ########.fr       */
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
	static	int count = 0;

	display = (t_display *)param;
	if (!number_in_array(1, (int []){MLX_PRESS}, keydata.action))
		return ;
	if (keydata.key == ESC)
		close_display(display);
	count++;
	printf("hola %d\n", count);
	// draw_map(display);
}
