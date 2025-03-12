#include "GAME.h"

unsigned int state = 777;

unsigned int my_rand(void)
{
   state = state * 1664525 + 1013904223;
   return state >> 24;
}

bool opponent_at_reach(t_game *game)
{
    // printf("pos: (%d,%d) opponent: (%d,%d)\n", game->y, game->x, game->opponent.y, game->opponent.x);

    const int dx = abs(game->x - game->opponent.x);
    const int dy = abs(game->y - game->opponent.y);

    if (dx <= 1 && dy <= 1)
        return (true);
    return (false);
}

bool move_horizontally(t_game *game)
{
    const int dx = abs(game->x - game->opponent.x);
    const int dy = abs(game->y - game->opponent.y);

    if (dx < dy)
        return (false);
    if (dx > dy)
        return (true);
    return (my_rand() % 2);
}

void chase_opponent(t_game *game)
{
    if (game->hunt_mode == false)
        return;

    if (game->opponent.y == -1 || game->opponent.x == -1)
        return;

    if (move_horizontally(game) == true)
    {
        if (game->opponent.x < game->x)
        {
            if (movement(game, MLX_KEY_LEFT))
                return;

            if (movement(game, MLX_KEY_UP))
                return;
            if (movement(game, MLX_KEY_DOWN))
                return;
        }
        else if (game->opponent.x > game->x)
        {
            if (movement(game, MLX_KEY_RIGHT))
                return;

            if (movement(game, MLX_KEY_UP))
                return;
            if (movement(game, MLX_KEY_DOWN))
                return;
        }
    }

    if (game->opponent.y < game->y)
    {
        if (movement(game, MLX_KEY_UP))
            return;
           
        if (movement(game, MLX_KEY_LEFT))
            return;
        if (movement(game, MLX_KEY_RIGHT))
            return;
    }
    else if (game->opponent.y > game->y)
    {
        if (movement(game, MLX_KEY_DOWN))
            return;
           
        if (movement(game, MLX_KEY_LEFT))
            return;
        if (movement(game, MLX_KEY_RIGHT))
            return;
    }
}
