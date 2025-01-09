#include "shared_functions.h"

void print_board(t_game *game)
{
    if (game->players == 0)
        ft_error("Empty map.");
    printf("printing board\n");
    for (int i = 0; i < BOARD_HEIGHT; i++)
        printf("%s\n", game->board[i]);
}

int main(void)
{
    void *memory_block = attach_memory_block(FILENAME, sizeof(t_game));

    t_game *game = (t_game *)memory_block;
    printf("players: %d\n", game->players);
    print_board(game);
    printf("MSG: {%s}\n", game->msg);
    printf("dettach: %d\n", dettach_memory_block(memory_block));
}
