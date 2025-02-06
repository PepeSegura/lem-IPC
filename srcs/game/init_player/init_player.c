#include "GAME.h"

size_t get_unix_timep(void)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}

int get_random_number(int pre_seed, int max)
{
    srand(get_unix_timep() + pre_seed);
    return (rand() % max);
}

void set_random_player_pos(t_shared *shared, t_game *player)
{
    for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
    {
        int random_x = get_random_number(i, BOARD_WIDTH);
        int random_y = get_random_number(i * i, BOARD_HEIGHT);
        if (shared->board[random_y][random_x] == '0')
        {
            printf("i:%d\n", i);
            player->x = random_x;
            player->y = random_y;
            return ;
        }
    }
    sem_post(player->sem);
    sem_close(player->sem);
    ft_error("Map is full.");
}

void init_player(t_game *game, t_shared *shared, char team_name)
{
    set_random_player_pos(shared, game);
    printf("new game pos: (%d,%d)\n", game->x, game->y);
    game->shared = shared;
    game->letter = ft_tolower(team_name);
    shared->board[game->y][game->x] = game->letter;
    shared->paint = 1;
    shared->players++;
}
