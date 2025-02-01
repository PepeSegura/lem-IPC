#include "GAME.h"

void	load_textures(t_game *player)
{
	player->images[0] = mlx_load_img(player->mlx, "sprites/UP.png");
	player->images[1] = mlx_load_img(player->mlx, "sprites/LEFT.png");
	player->images[2] = mlx_load_img(player->mlx, "sprites/RIGHT.png");
	player->images[3] = mlx_load_img(player->mlx, "sprites/DOWN.png");
	for (int i = 0; i < 4; i++)
		mlx_resize_image(player->images[i], player->images[i]->width * 2, player->images[i]->height * 2);
}

mlx_t	*init_and_customize_mlx(void)
{
	mlx_t				*mlx;
	mlx_win_cursor_t	*cursor;

	mlx = mlx_init(TILE_WIDTH * 3, TILE_WIDTH * 3, "player", false);
	if (mlx == NULL)
		ft_error("Can't load mlx");
	cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(mlx, cursor);
	return (mlx);
}
