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
