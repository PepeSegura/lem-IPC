/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_nearest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:14 by psegura-          #+#    #+#             */
/*   Updated: 2025/03/10 16:43:17 by psegura-         ###   ########.fr       */
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

int	count_team_members(t_game *game_data, char team_name)
{
	int team_count = 0;

	sem_wait(game_data->sem);
	for (size_t y = 0; y < BOARD_HEIGHT; y++)
	{
		for (size_t x = 0; x < BOARD_WIDTH; x++)
		{
			if (game_data->shared->board[y][x] == team_name)
				team_count++;
		}
		
	}
	sem_post(game_data->sem);
	return (team_count);
}

int	fill_our_team_array(t_player_position *our_team, t_game *game_data)
{
	int team_count = 0;

	sem_wait(game_data->sem);
	for (size_t y = 0; y < BOARD_HEIGHT; y++)
	{
		for (size_t x = 0; x < BOARD_WIDTH; x++)
		{
			if (game_data->shared->board[y][x] == game_data->team_name)
			{
				our_team[team_count].team = game_data->team_name;
				our_team[team_count].x = x;
				our_team[team_count].y = y;
				our_team[team_count].distance = 0;
				team_count++;
			}
		}
		
	}
	sem_post(game_data->sem);
	return (team_count);
}

int	fill_opponents_array(t_player_position *opponents, t_game *game_data)
{
	int opponents_count = 0;

	sem_wait(game_data->sem);
	for (size_t y = 0; y < BOARD_HEIGHT; y++)
	{
		for (size_t x = 0; x < BOARD_WIDTH; x++)
		{
			if (game_data->shared->board[y][x] != game_data->team_name && game_data->shared->board[y][x] != '0')
			{
				// printf("OP_TEAM: %c\n", game_data->shared->board[y][x]);
				opponents[opponents_count].team = game_data->shared->board[y][x];
				opponents[opponents_count].x = x;
				opponents[opponents_count].y = y;
				opponents[opponents_count].distance = 0;
				opponents_count++;
			}
		}
	}
	sem_post(game_data->sem);
	return (opponents_count);
}

int	find_nearest_oponent(t_game *game_data)
{
	t_player_position   our_team[BOARD_SIZE];
	t_player_position   opponents[BOARD_SIZE];

	ft_memset(our_team, 0, sizeof(our_team));
	ft_memset(opponents, 0, sizeof(opponents));

	int our_team_count = fill_our_team_array(our_team, game_data);
	int opponents_count = fill_opponents_array(opponents, game_data);
	// printf("our_team_count:  [%d]\n", our_team_count);
	// printf("opponents_count: [%d]\n", opponents_count);

	t_closest_oponent closest_oponents[26] = {0};

	for (int i = 0; i < 26; i++)
		closest_oponents[i].distance = INT32_MAX;

	for (int i = 0; i < opponents_count; i++)
	{
		int total_distance = 0;
		for (int j = 0; j < our_team_count; j++)
			total_distance += calc_distance(our_team[j], opponents[i].x, opponents[i].y);
		
		// printf("TOTAAAAL distance: %d\n", total_distance);
		int team_name_offset = opponents[i].team - 'a';
		// printf("index: %d - distance node: %d\n", team_name_offset, closest_oponents[team_name_offset].distance);
		if (total_distance < closest_oponents[team_name_offset].distance)
		{
			closest_oponents[team_name_offset].distance = total_distance;
			closest_oponents[team_name_offset].x = opponents[i].x;
			closest_oponents[team_name_offset].y = opponents[i].y;
		}
	}

	// printf("Closest opponent distances and coordinates for team A:\n");
	int	min_distance = INT32_MAX;
	for (int i = 0; i < 26; i++)
	{
		if (closest_oponents[i].distance != INT32_MAX)
		{
			// printf("BEEEEFFFF - Opponent Team: %c, Total Distance: %d, Coordinates: (%d, %d)\n", i + 'A', closest_oponents[i].distance, closest_oponents[i].x, closest_oponents[i].y);
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
			printf("Closest Opponent:\n");
			printf("Team_%c, Total Distance: %d, Coordinates: (%d, %d)\n", i + 'A', closest_oponents[i].distance, closest_oponents[i].x, closest_oponents[i].y);
			message.x = closest_oponents[i].x;
			message.y = closest_oponents[i].y;
			break;
		}
	}

	if (message.y == -1 || message.x == -1)
	{
		printf("No oponent was found.\n");
		return (0);
	}

	sem_wait(game_data->sem);
	if (game_data->own_pid == game_data->shared->teams_masters_pids[(int)game_data->team_name])
		msgsnd(game_data->queue_id, &message, sizeof(message) - sizeof(long), 0);
	sem_post(game_data->sem);
	return (0);
}
