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

char	*gen_filename(char letter)
{
	return (ft_ultrajoin("sprites/", (char [2]){letter, '\0'}, ".png", NULL));
}

void	*load_textures(t_display *display)
{
	display->images['0'] = mlx_load_img(display->mlx, "sprites/blank.png");
	if (display->images['0'] == NULL)
		return (NULL);
	for (unsigned char letter = 'a'; letter <= 'z'; letter++)
	{
		char	*name = gen_filename(letter);
		display->images[letter] = mlx_load_img(display->mlx, name);
		free(name);
		if (display->images[letter] == NULL)
			return (NULL);
	}
	return ((void *)1);
}
