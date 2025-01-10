/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/10 21:16:00 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

mlx_t	*init_and_customize_mlx(void)
{
	mlx_t				*mlx;
	mlx_win_cursor_t	*cursor;

	mlx = mlx_init(BOARD_WIDTH * 64, BOARD_HEIGHT * 64, "board", false);
	if (mlx == NULL)
		ft_error("Can't load mlx");
	cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(mlx, cursor);
	return (mlx);
}

char  *gen_name(char letter)
{
	char *letter_arr = malloc(30 * sizeof(char));

	sprintf(letter_arr, "sprites/%c.png", letter);
	return (letter_arr);
}

void	load_textures(t_display *display)
{
	display->images = ft_calloc(sizeof(mlx_image_t *), (TEXTURES_COUNT + 1));
	mlx_texture_t *new_texture;

	new_texture =  mlx_load_png("sprites/blank.png");
	display->images[BLANK] = mlx_texture_to_image(display->mlx, new_texture);
	mlx_delete_texture(new_texture);


	int i = 1;
	for (unsigned char letter = 'a'; letter <= 'z'; letter++, i++)
	{
		char *name = gen_name(letter);
		printf("name: %s\n", name);
		mlx_texture_t *new_texture = mlx_load_png(name);
		display->images[i] = mlx_texture_to_image(display->mlx, new_texture);
		mlx_delete_texture(new_texture);
		free(name);
	}
}

void drawn_map(t_display *display)
{
	int i, j;

	i = 0;
	while (i < BOARD_HEIGHT)
	{
		j = 0;
		while (j < BOARD_WIDTH)
		{
			mlx_image_to_window(display->mlx, display->images[BLANK], j * 64, i * 64);
			j++;
		}
		i++;
	}
}

void	mlx_stuff(t_display *display)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx();
	display->mlx = mlx;
	load_textures(display);
	img = mlx_new_image(mlx, BOARD_WIDTH * 64, BOARD_HEIGHT * 64);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	display->img = img;
	drawn_map(display);
	mlx_image_to_window(mlx, display->images[A], 10*64, 10 * 64);
	mlx_image_to_window(mlx, display->images[B], 2*64, 4*64);
	mlx_image_to_window(mlx, display->images[C], 22*64, 15*64);
	mlx_image_to_window(mlx, display->images[D], 32*64, 16*64);

	mlx_key_hook(mlx, my_key_hook, display);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

int	main(void)
{
	t_display display;

	ft_bzero(&display, sizeof(t_display));
	mlx_stuff(&display);
	exit(EXIT_SUCCESS);
}
