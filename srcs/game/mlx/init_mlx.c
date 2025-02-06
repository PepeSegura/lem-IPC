#include "GAME.h"

char  *gen_filename(char letter)
{
	return (ft_ultrajoin("sprites/", (char [2]){letter, '\0'}, ".png", NULL));
}

void	load_textures(t_game *player)
{
	player->images[WALL]	  = mlx_load_img(player->mlx, "sprites/wall.png");

	// mlx_resize_image(player->images[WALL], player->images[WALL]->width * 2, player->images[WALL]->height * 2);

	player->images['0'] = mlx_load_img(player->mlx, "sprites/blank.png");
	// mlx_resize_image(player->images['0'], player->images['0']->width * 2, player->images['0']->height * 2);
	for (unsigned char letter = 'a'; letter <= 'z'; letter++)
	{
		char *name = gen_filename(letter);
		player->images[letter] = mlx_load_img(player->mlx, name);
		// mlx_resize_image(player->images[letter], player->images[letter]->width * 2, player->images[letter]->height * 2);
		free(name);
	}
}

mlx_t	*init_and_customize_mlx(void)
{
	mlx_t				*mlx;
	mlx_win_cursor_t	*cursor;

	mlx = mlx_init(TILE * 3, TILE * 4, "player", false);
	if (mlx == NULL)
		ft_error("Can't load mlx");
	cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(mlx, cursor);
	return (mlx);
}
