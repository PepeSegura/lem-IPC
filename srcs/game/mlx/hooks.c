#include "GAME.h"

void	close_player(t_game *player)
{
	ft_printf("Escape!\n");
	mlx_terminate(player->mlx);
	if (player->sem != SEM_FAILED)
		sem_close(player->sem);
	exit(0);
}

char *get_player_pos(int x, int y)
{
	char *str_x = ft_itoa(x);
	char *str_y = ft_itoa(y);

	char *first = ft_strjoin("Player pos: (", str_x);
	char *middle = ft_strjoin(first, ",");
	char *second = ft_strjoin(middle, str_y);
	char *player_pos = ft_strjoin(second, ")");
	free(str_x), free(str_y), free(first), free(middle), free(second);
	return (player_pos);
}

void	movement(t_game *game, int key)
{
	int x = 0;
	int y = 0;

	if (key == MLX_KEY_UP)		y = -1;
	if (key == MLX_KEY_LEFT)	x = -1;
	if (key == MLX_KEY_RIGHT)	x = 1;
	if (key == MLX_KEY_DOWN)	y = 1;

	sem_wait(game->sem);

	printf("(%d,%d) = %c\n", game->y, game->x, game->shared->board[game->y][game->x]);
	game->shared->board[game->y][game->x] = '0';
	game->x += x;
	game->y += y;


	if ((game->x < 0 || game->x >= BOARD_WIDTH) || (game->y < 0 || game->y >= BOARD_HEIGHT))
	{
		game->x -= x;
		game->y -= y;
	}

	game->shared->board[game->y][game->x] = game->letter;
	game->shared->paint = 1;

	sem_post(game->sem);
	char *player_pos = get_player_pos(game->y, game->x);
	game->str_img = mlx_put_string(game->mlx, player_pos, 0, 0);
	free(player_pos);
}

void draw_arrows(t_game *game)
{
	mlx_image_to_window(game->mlx, game->images[UP], TILE_WIDTH, 0 + TILE_WIDTH);
    mlx_image_to_window(game->mlx, game->images[LEFT], 0, TILE_WIDTH + TILE_WIDTH);
    mlx_image_to_window(game->mlx, game->images[RIGHT], TILE_WIDTH * 2, TILE_WIDTH + TILE_WIDTH);
    mlx_image_to_window(game->mlx, game->images[DOWN], TILE_WIDTH, TILE_WIDTH + TILE_WIDTH);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;
	if (!number_in_array(1, (int []){MLX_PRESS}, keydata.action))
		return ;
	if (keydata.key == ESC)
		close_player(game);
	if (game->str_img)
		mlx_delete_image(game->mlx, game->str_img);
	movement(game, keydata.key);
	draw_arrows(game);
}
