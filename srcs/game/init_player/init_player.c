/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:42:51 by psegura-          #+#    #+#             */
/*   Updated: 2025/03/10 13:11:56 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

size_t	get_unix_timep(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

int	get_random_number(int pre_seed, int max)
{
	srand(get_unix_timep() + pre_seed);
	return (rand() % max);
}

void	set_random_player_pos(t_shared *shared, t_game *player)
{
	for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
	{
		int	random_x = get_random_number(i, BOARD_WIDTH);
		int	random_y = get_random_number(i * i, BOARD_HEIGHT);
		if (shared->board[random_y][random_x] == '0')
		{
			player->x = random_x;
			player->y = random_y;
			return ;
		}
	}
	sem_post(player->sem);
	sem_close(player->sem);
	ft_error("Map is full.");
}

void	init_player(t_game *game, t_shared *shared, char team_name)
{
	if (shared->teams_players_count[(int)team_name] >=2)
	{
		printf("Can't join game: Team %c is already full\n", ft_toupper(team_name));
		sem_post(game->sem);
		exit(1);
	}
	if (shared->teams_players_count[(int)team_name] == 0)
	{
		printf("Creating queue for team %c\n", ft_toupper(team_name));
		game->queue_id = get_or_create_msg_queue(FILENAME, team_name, true);
	}
	else
	{
		printf("Getting queue for team %c\n", ft_toupper(team_name));
		game->queue_id = get_or_create_msg_queue(FILENAME, team_name, false);
	}


	set_random_player_pos(shared, game);
	printf("new game pos: (%d,%d)\n", game->x, game->y);
	game->shared = shared;
	game->team_name = team_name;
	shared->board[game->y][game->x] = game->team_name;
	shared->paint = 1;
	shared->total_players_count++;
	shared->teams_players_count[(int)team_name]++;
	game->own_pid = getpid();
	set_team_master(game);
}
