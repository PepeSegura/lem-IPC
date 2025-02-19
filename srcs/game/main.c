#include "GAME.h"

void	mlx_stuff(t_game *game)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx();
	game->mlx = mlx;
	if (load_textures(game) == NULL)
        leave_board(game);
	img = mlx_new_image(mlx, TILE * 3, TILE * 3);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	game->img = img;

	char *player_pos = get_player_pos(game->x, game->y);
	game->str_img = mlx_put_string(game->mlx, player_pos, TILE / 10, TILE / 10);
	free(player_pos);

    draw_minimap(game);
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
