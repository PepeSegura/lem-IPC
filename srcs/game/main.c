/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:26:50 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/29 20:37:52 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

void	mlx_stuff(t_game *player)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx();
	player->mlx = mlx;
	// load_textures(player);
	img = mlx_new_image(mlx, BOARD_WIDTH * 64, BOARD_HEIGHT * 64);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	player->img = img;
	mlx_key_hook(mlx, my_key_hook, player);
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
    
    printf("dettach: %d\n", dettach_memory_block((void *)shared));
    sem_post(player.sem);
    mlx_stuff(&player);
    sem_close(player.sem);
}
