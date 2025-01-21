/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/21 16:21:15 by psegura-         ###   ########.fr       */
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
	mlx_texture_t *new_texture;

	new_texture =  mlx_load_png("sprites/blank.png");
	display->images['0'] = mlx_texture_to_image(display->mlx, new_texture);
	mlx_delete_texture(new_texture);

	for (unsigned char letter = 'a'; letter <= 'z'; letter++)
	{
		char *name = gen_name(letter);
		mlx_texture_t *new_texture = mlx_load_png(name);
		display->images[letter] = mlx_texture_to_image(display->mlx, new_texture);
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
			int letter = display->data->board[i][j];
			mlx_image_to_window(display->mlx, display->images[letter], j * 64, i * 64);
			j++;
		}
		i++;
	}
}

void loop_hook(void *param)
{
	static double time = 0.0;
	t_display		*display;

	display = (t_display *)param;
	time += display->mlx->delta_time;
	if (time >= 1.0)
	{
		printf("time %f\n", time);
		time = 0.0;
		drawn_map(display);
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
	mlx_key_hook(mlx, my_key_hook, display);
	mlx_loop_hook(mlx, loop_hook, display);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void print_board(t_shared *game)
{
    if (game->players == 0)
        ft_error("Empty map.");
    printf("printing board\n");
    for (int i = 0; i < BOARD_HEIGHT; i++)
        printf("%s\n", game->board[i]);
}

void load_shared_memory(t_display *display)
{
	(void)display;
	void *memory_block;

	for (int i = 1; i <= 60; i++)
	{	
		memory_block = attach_memory_block(FILENAME, sizeof(t_shared), false);
		if (memory_block == NULL)
		{
			if (i == 60)
				exit(1);
			ft_dprintf(1, "%d/60: Trying to load shared memory, launch a player to generate the board.\n", i);
			usleep(500 * 1000);
		}
		else
			break;
	}

    t_shared *data = (t_shared *)memory_block;
    printf("players: %d\n", data->players);
    print_board(data);
    printf("MSG: {%s}\n", data->msg);
    // printf("dettach: %d\n", dettach_memory_block(memory_block));
	display->data = data;
}

int	main(void)
{
	// daemon(1, 0);
	t_display display = {0};

	load_shared_memory(&display);
	mlx_stuff(&display);
	exit(EXIT_SUCCESS);
}
