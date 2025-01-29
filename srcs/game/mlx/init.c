#include "GAME.h"

void	load_textures(t_game *player)
{
	mlx_texture_t *new_texture;

	new_texture =  mlx_load_png("sprites/blank.png");
	player->images[0] = mlx_texture_to_image(player->mlx, new_texture);
	mlx_delete_texture(new_texture);
}

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
