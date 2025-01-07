#include "shared_functions.h"

void print_board(t_game *game)
{
    printf("printing board\n");

    int i = 0;
    while (i < BOARD_HEIGHT)
    {
        printf("%s\n", game->board[i]);
        i++;
    }
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
