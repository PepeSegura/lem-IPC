/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:26:50 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/21 16:22:29 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PLAYER.h"

void fill_board(t_shared *game)
{
    memset(game->board, '0', sizeof(game->board));
    for (int i = 0; i < BOARD_HEIGHT; i++)
        game->board[i][BOARD_WIDTH] = '\0';
}

int main(int argc, char **argv)
{
    (void)argc, (void)argv;
    if (argc != 2)
        ft_error("Invalid number of arguments.");

    if (ft_strlen(argv[1]) > 1)
        ft_error("Player team must be a letter.");

    printf("Hello, this is a player!!\n");

    printf("sizeof(t_shared) = %ld\n", sizeof(t_shared));
    void *memory_block = attach_memory_block(FILENAME, sizeof(t_shared), true);
    if (memory_block == NULL)
    {
        ft_error("Can't load shared memory.");
    }
    t_shared *game = (t_shared *)memory_block;

    if (game->players != 42)
    {
        game->players = 42;
        fill_board(game);
        game->board[0][0] = ft_tolower(argv[1][0]);
    }
    else
        game->board[0][0] = argv[1][0];
    printf("writing {%s} into memory\n", argv[1]);
    sprintf(game->msg, "%s", argv[1]);
    printf("dettach: %d\n", dettach_memory_block(memory_block));
}
