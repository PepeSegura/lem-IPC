/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:50:25 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 15:27:57 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

void	leave_board(t_game *game)
{
	int	close_game = 0;

	sem_wait(game->sem);
	game->shared->board[game->y][game->x] = '0';
	game->shared->paint = 1;
	game->shared->players--;
	if (game->shared->players == 0)
		close_game = 1;
	sem_post(game->sem);
	if (game->sem != SEM_FAILED)
		sem_close(game->sem);
	if (close_game == 1)
	{
		int	sem_ret = sem_unlink(SEM_NAME);
		if (sem_ret == -1)
		{
			perror("sem_unlink");
			exit(1);
		}
		if (game->shared->display_pid != -42)
			kill(game->shared->display_pid, SIGUSR1);
		printf("deleting shared memory\n");
		int	destroy_ret = destroy_memory_block(FILENAME, false);
		if (destroy_ret == 1)
			printf("Cannot clear shared memory, close first the display\n");
	}
	exit(0);
}

void	close_player(t_game *game)
{
	mlx_terminate(game->mlx);
	leave_board(game);
	exit(0);
}

char	*get_player_pos(int x, int y)
{
	char	*str_x = ft_itoa(x);
	char	*str_y = ft_itoa(y);
	char	*final = ft_ultrajoin("Player pos: (", str_x, ",", str_y, ")", NULL);

	free(str_x), free(str_y);
	return (final);
}

static void	write_player_pos(t_game *game)
{
	char	*player_pos = get_player_pos(game->y, game->x);
	game->str_img = mlx_put_string(game->mlx, player_pos, TILE / 10, TILE / 10);
	free(player_pos);
}

static void	check_pos(t_game *game, char (*array)[256], int pos_x, int pos_y)
{
	if ((pos_x < 0 || pos_x >= BOARD_WIDTH) || (pos_y < 0 || pos_y >= BOARD_HEIGHT))
		return ;
	if (game->shared->board[pos_y][pos_x] != '0')
		(*array)[(int)game->shared->board[pos_y][pos_x]] += 1;
}

static int	is_surrounded(t_game *game)
{
	char	array[256];

	ft_memset(array, 0, sizeof(array));

	/* TOP */
	check_pos(game, &array, game->x - 1, game->y - 1);
	check_pos(game, &array, game->x - 0, game->y - 1);
	check_pos(game, &array, game->x + 1, game->y - 1);

	/* SIDES */
	check_pos(game, &array, game->x - 1, game->y + 0);
	check_pos(game, &array, game->x + 1, game->y + 0);

	/* BOTTOM */
	check_pos(game, &array, game->x - 1, game->y + 1);
	check_pos(game, &array, game->x - 0, game->y + 1);
	check_pos(game, &array, game->x + 1, game->y + 1);

	for (int letter = 'a'; letter < 'z'; letter++)
	{
		if (array[letter] > 1 && letter != game->letter)
		{
			printf("Closing game...\nYou have been sorrounded by TEAM_[%c] with [%d] players\n", ft_toupper(letter), array[letter]);
			sem_post(game->sem);
			close_player(game);
			return (true);
		}
	}
	return (false);
}

static void	restore_pos(t_game *game, int x, int y)
{
	game->x -= x;
	game->y -= y;
	sem_post(game->sem);
	write_player_pos(game);
}

static int	is_a_valid_move(t_game *game, int x, int y)
{

	if ((game->x < 0 || game->x >= BOARD_WIDTH) || (game->y < 0 || game->y >= BOARD_HEIGHT))
	{
		restore_pos(game, x, y);
		return (false);
	}
	if (game->shared->board[game->y][game->x] != '0')
	{
		restore_pos(game, x, y);
		return (false);
	}
	return (true);
}

static void	movement(t_game *game, int key)
{
	int	x = 0;
	int	y = 0;

	if (key == MLX_KEY_UP)		y = -1;
	if (key == MLX_KEY_LEFT)	x = -1;
	if (key == MLX_KEY_RIGHT)	x = 1;
	if (key == MLX_KEY_DOWN)	y = 1;

	sem_wait(game->sem);

	if (is_surrounded(game) == true)
		return ;

	game->x += x;
	game->y += y;

	if (is_a_valid_move(game, x, y) == false)
		return ;

	game->shared->board[game->y - y][game->x - x] = '0';
	game->shared->board[game->y][game->x] = game->letter;
	game->shared->paint = 1;

	sem_post(game->sem);
	write_player_pos(game);
}

static void	paint_cord(t_game *game, int pos_x, int pos_y, int x, int y)
{
	if ((pos_x < 0 || pos_x >= BOARD_WIDTH) || (pos_y < 0 || pos_y >= BOARD_HEIGHT))
	{
		mlx_image_to_window(game->mlx, game->images[WALL], x, y);
		return ;
	}
	mlx_image_to_window(game->mlx, game->images[(int)game->shared->board[pos_y][pos_x]], x, y);
}


void	draw_minimap(t_game *game)
{
	sem_wait(game->sem);

	/* TOP_ROW */
	paint_cord(game, game->x - 1, game->y - 1, 0, 0 + TILE);
	paint_cord(game, game->x, game->y - 1, TILE, 0 + TILE);
	paint_cord(game, game->x + 1, game->y - 1, (TILE * 2), 0 + TILE);

	/* PLAYER_ROW */
	paint_cord(game, game->x - 1, game->y, 0, TILE + TILE);
	paint_cord(game, game->x, game->y, TILE, TILE + TILE);
	paint_cord(game, game->x + 1, game->y, (TILE * 2), TILE + TILE);

	/* BOTTOM_ROW */
	paint_cord(game, game->x - 1, game->y + 1, 0, (TILE * 2) + TILE);
	paint_cord(game, game->x, game->y + 1, TILE, (TILE * 2) + TILE);
	paint_cord(game, game->x + 1, game->y + 1, (TILE * 2), (TILE * 2) + TILE);

	sem_post(game->sem);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_player(game);
	if (game->str_img)
		mlx_delete_image(game->mlx, game->str_img);
	movement(game, keydata.key);
	draw_minimap(game);
}
