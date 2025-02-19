#include "GAME.h"

void fill_board(t_shared *game)
{
    ft_memset(game->board, '0', sizeof(game->board));
    for (int i = 0; i < BOARD_HEIGHT; i++)
        game->board[i][BOARD_WIDTH] = '\0';
}

void    init_game(t_shared *shared)
{
    if (shared->started == 0)
    {
        shared->started = 1;
        shared->paint = 1;
        shared->players = 0;
        shared->display_pid = -42;
        fill_board(shared);
    }
}
