/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:00:23 by psegura-          #+#    #+#             */
/*   Updated: 2025/03/10 13:10:41 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

mlx_t	*init_and_customize_mlx(void)
{
	mlx_t				*mlx;
	mlx_win_cursor_t	*cursor;

	mlx = mlx_init(BOARD_WIDTH * 64, BOARD_HEIGHT * 64, "DISPLAY", false);
	if (mlx == NULL)
		ft_error("Can't load mlx");
	cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(mlx, cursor);
	return (mlx);
}

char	*gen_filename(char team_name)
{
	return (ft_ultrajoin("sprites/", (char [2]){team_name, '\0'}, ".png", NULL));
}

void	*load_textures(t_display *display)
{
	display->images['0'] = mlx_load_img(display->mlx, "sprites/blank.png");
	if (display->images['0'] == NULL)
		return (NULL);
	for (unsigned char team_name = 'a'; team_name <= 'z'; team_name++)
	{
		char	*name = gen_filename(team_name);
		display->images[team_name] = mlx_load_img(display->mlx, name);
		free(name);
		if (display->images[team_name] == NULL)
			return (NULL);
	}
	return ((void *)1);
}

void loop_hook(void *param)
{
	static double	time = 0.0;
	t_display		*display;

	display = (t_display *)param;
	time += display->mlx->delta_time;
	if (time >= 0.5)
	{
		if (end_program == true)
			close_display(display);
		time = 0.0;
		draw_map(display);
	}
}

void	mlx_stuff(t_display *display)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx();
	display->mlx = mlx;
	if (load_textures(display) == NULL)
		close_board(display);
	img = mlx_new_image(mlx, BOARD_WIDTH * 64, BOARD_HEIGHT * 64);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	display->img = img;
	draw_map(display);
	mlx_key_hook(mlx, my_key_hook, display);
	mlx_loop_hook(mlx, loop_hook, display);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
