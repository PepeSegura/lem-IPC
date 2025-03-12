/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_nearest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:14 by psegura-          #+#    #+#             */
/*   Updated: 2025/03/12 18:23:19 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

typedef struct s_player_position
{
	char    team;
	int     x;
	int     y;
	int     distance;
}   t_player_position;

typedef struct s_closest_oponent
{
	int	distance;
	int x;
	int y;
}   t_closest_oponent;

int	calc_distance(t_player_position a, int x, int y)
{
	return (abs(a.x - x) + abs(a.y -y));
}

void	fill_board_arrays(t_player_position *our_team, t_player_position *opponents, t_game *game_data, int *our_team_count, int *opponents_count)
{
	sem_wait(game_data->sem);
	for (size_t y = 0; y < BOARD_HEIGHT; y++)
	{
		for (size_t x = 0; x < BOARD_WIDTH; x++)
		{
			if (game_data->shared->board[y][x] == game_data->team_name)
			{
				our_team[*our_team_count].team = game_data->team_name;
				our_team[*our_team_count].x = x;
				our_team[*our_team_count].y = y;
				our_team[*our_team_count].distance = 0;
				(*our_team_count)++;
			}
			if (game_data->shared->board[y][x] != game_data->team_name && game_data->shared->board[y][x] != '0')
			{
				opponents[*opponents_count].team = game_data->shared->board[y][x];
				opponents[*opponents_count].x = x;
				opponents[*opponents_count].y = y;
				opponents[*opponents_count].distance = 0;
				(*opponents_count)++;
			}
		}
	}
	sem_post(game_data->sem);
}

void	find_nearest_oponent(t_game *game_data)
{
    if (game_data->hunt_mode == false)
        return;
	bool	is_master = false;

	sem_wait(game_data->sem);
	if (game_data->own_pid == game_data->shared->teams_masters_pids[(int)game_data->team_name])
		is_master = true;
	sem_post(game_data->sem);

	if (is_master == false)
		return ;

	t_player_position   our_team[BOARD_SIZE];
	t_player_position   opponents[BOARD_SIZE];

	ft_memset(our_team, 0, sizeof(our_team));
	ft_memset(opponents, 0, sizeof(opponents));

	int our_team_count = 0;
	int opponents_count = 0;

	fill_board_arrays(our_team, opponents, game_data, &our_team_count, &opponents_count);

	t_closest_oponent closest_oponents[26] = {0};

	for (int i = 0; i < 26; i++)
		closest_oponents[i].distance = INT32_MAX;

	for (int i = 0; i < opponents_count; i++)
	{
		int total_distance = 0;
		for (int j = 0; j < our_team_count; j++)
			total_distance += calc_distance(our_team[j], opponents[i].x, opponents[i].y);
		
		int team_name_offset = opponents[i].team - 'a';
		if (total_distance < closest_oponents[team_name_offset].distance)
		{
			closest_oponents[team_name_offset].distance = total_distance;
			closest_oponents[team_name_offset].x = opponents[i].x;
			closest_oponents[team_name_offset].y = opponents[i].y;
		}
	}

	int	min_distance = INT32_MAX;
	for (int i = 0; i < 26; i++)
	{
		if (closest_oponents[i].distance != INT32_MAX)
		{
			if (closest_oponents[i].distance < min_distance)
				min_distance = closest_oponents[i].distance;
		}
	}

	t_msg message = {.mtype = 1, .y = -1, .x = -1};

	for (int i = 0; i < 26; i++)
	{
		if (closest_oponents[i].distance == INT32_MAX)
			continue;
		if (closest_oponents[i].distance == min_distance)
		{
			// printf("Opponent %c found (%d,%d)\n", i + 'A', closest_oponents[i].y, closest_oponents[i].x);
			message.y = closest_oponents[i].y;
			message.x = closest_oponents[i].x;
			break;
		}
	}

	// if (message.y == -1 || message.x == -1)
	// 	printf("No oponent was found.\n");

	game_data->opponent.y = message.y;
	game_data->opponent.x = message.x;

	msgsnd(game_data->queue_id, &message, sizeof(message) - sizeof(long), 0);
}
