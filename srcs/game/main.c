/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:00:46 by psegura-          #+#    #+#             */
/*   Updated: 2025/03/12 18:23:48 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

void read_msg_queue(t_game *game)
{
	if (game->own_pid == game->shared->teams_masters_pids[(int)game->team_name])
		return;
	if (game->queue_id == -1)
		return;
	t_msg	message = {.x = -1, .y = -1};

	while(1)
	{
		if (msgrcv(game->queue_id, &message, sizeof(message) - sizeof(long), 1, IPC_NOWAIT) == -1)
			break;
		game->opponent.y = message.y;
		game->opponent.x = message.x;
	}


	if (game->opponent.x == -1 || game->opponent.y == -1)
		return;
	
	// printf("Opponent new pos: (%d,%d)\n", game->opponent.y, game->opponent.x);
}

void loop_hook(void *param)
{
	static double	time = 0.0;
	t_game          *game;

	game = (t_game *)param;
	time += game->mlx->delta_time;
	if (time >= 1.00)
	{
		if (exit_signal == 1)
			close_player(game);
		if (game->hunt_mode == true)
			find_nearest_oponent(game);
		sem_wait(game->sem);
		read_msg_queue(game);
		set_team_master(game);
		sem_post(game->sem);
		if (game->hunt_mode == true)
			chase_opponent(game);
		draw_minimap(game);
		time = 0.0;
	}
}

char *gen_team_name(char team_name)
{
	return (ft_ultrajoin("TEAM_", (char [2]){ft_toupper(team_name), '\0'}, NULL));
}

void	mlx_stuff(t_game *game)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (exit_signal == 1)
		exit(0);
	mlx = init_and_customize_mlx(gen_team_name(game->team_name));
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
    mlx_loop_hook(mlx, loop_hook, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}


void sig_handler(int signum)
{
	ft_dprintf(2, "Closing player: signal(%d) - %s\n", signum, strsignal(signum));
	exit_signal = 1;
}

int exit_signal = 0;

int main(int argc, char **argv)
{
	signal(SIGINT, sig_handler);
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
	leave_board(&player);
}
