#include "shared_functions.h"

void fill_board(t_game *game)
{
    memset(game->board, '0', sizeof(game->board));
    for (int i = 0; i < BOARD_HEIGHT; i++)
        game->board[i][BOARD_WIDTH] = '\0';
}

int main(int argc, char **argv)
{
    if (argc != 2)
        ft_error("Invalid number of arguments.");

    if (strlen(argv[1]) >= BLOCK_SIZE)
        ft_error("Msg bigger than memory block.");

    printf("sizeof(t_game) = %ld\n", sizeof(t_game));
    void *memory_block = attach_memory_block(FILENAME, sizeof(t_game));

    t_game *game = (t_game *)memory_block;

    if (game->players != 42)
    {
        game->players = 42;
        fill_board(game);
        game->board[0][0] = 'A';
    }
    else
        game->board[0][0] = argv[1][0];
    printf("writing {%s} into memory\n", argv[1]);
    sprintf(game->msg, "%s", argv[1]);
    printf("dettach: %d\n", dettach_memory_block(memory_block));
}