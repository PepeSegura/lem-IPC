/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:26:50 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/01 21:01:23 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"


void	mlx_stuff(t_game *game)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx();
	game->mlx = mlx;
	load_textures(game);
	img = mlx_new_image(mlx, TILE_WIDTH * 3, TILE_WIDTH * 3);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	game->img = img;

	char *player_pos = get_player_pos(game->x, game->y);
	game->str_img = mlx_put_string(game->mlx, player_pos, 0, 0);
	free(player_pos);

    mlx_image_to_window(game->mlx, game->images[UP], TILE_WIDTH, 0 + TILE_WIDTH);
    mlx_image_to_window(game->mlx, game->images[LEFT], 0, TILE_WIDTH + TILE_WIDTH);
    mlx_image_to_window(game->mlx, game->images[RIGHT], TILE_WIDTH * 2, TILE_WIDTH + TILE_WIDTH);
    mlx_image_to_window(game->mlx, game->images[DOWN], TILE_WIDTH, TILE_WIDTH + TILE_WIDTH);

    
	mlx_key_hook(mlx, my_key_hook, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void print_board(t_shared *shared)
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
        printf("[%d] - [%s]\n", i, shared->board[i]);
}

int main(int argc, char **argv)
{
    char team_name = parser(argc, argv);

    t_game player;

    ft_memset(&player, 0, sizeof(t_game));
    init_semaphores(&player);

    sem_wait(player.sem);

    t_shared *shared = attach_or_create_shared_memory();

    init_game(shared);
    init_player(&player, shared, team_name);
    
    sem_post(player.sem);
    mlx_stuff(&player);
    printf("dettach: %d\n", dettach_memory_block((void *)shared));
    sem_close(player.sem);
}
