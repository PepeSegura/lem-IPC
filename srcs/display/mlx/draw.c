/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:15:34 by psegura-          #+#    #+#             */
/*   Updated: 2025/03/10 13:10:41 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

void draw_map(t_display *display)
{
	int i, j, team_name;

	i = 0;
	sem_wait(display->sem);
	if (display->shared->paint == 0)
	{
		sem_post(display->sem);
		return ;
	}
	while (i < BOARD_HEIGHT)
	{
		j = 0;
		while (j < BOARD_WIDTH)
		{
			team_name = display->shared->board[i][j];
			mlx_image_to_window(display->mlx, display->images[team_name], j * 64, i * 64);
			j++;
		}
		i++;
	}
	display->shared->paint = 0;
	sem_post(display->sem);
}
