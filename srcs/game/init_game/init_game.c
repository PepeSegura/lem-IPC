/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:45:59 by psegura-          #+#    #+#             */
/*   Updated: 2025/03/10 12:52:29 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

void	fill_board(t_shared *game)
{
	ft_memset(game->board, '0', sizeof(game->board));
	for (int i = 0; i < BOARD_HEIGHT; i++)
		game->board[i][BOARD_WIDTH] = '\0';
}

void	init_game(t_shared *shared)
{
	if (shared->started == 0)
	{
		shared->started = 1;
		shared->paint = 1;
		shared->total_players_count = 0;
		shared->display_pid = -42;
		fill_board(shared);
	}
}
