/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:26:50 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/22 12:39:55 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PLAYER.h"

void fill_board(t_shared *game)
{
    memset(game->board, '0', sizeof(game->board));
    for (int i = 0; i < BOARD_HEIGHT; i++)
        game->board[i][BOARD_WIDTH] = '\0';
}

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

void set_random_player_pos(t_shared *shared, t_player *player)
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

void	close_player(t_player *player)
{
	ft_printf("Escape!\n");
	mlx_terminate(player->mlx);
	if (player->sem != SEM_FAILED)
		sem_close(player->sem);
	exit(0);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	if (!number_in_array(1, (int []){MLX_PRESS}, keydata.action))
		return ;
	if (keydata.key == ESC)
		close_player((t_player *)param);
}

void	load_textures(t_player *player)
{
	mlx_texture_t *new_texture;

	new_texture =  mlx_load_png("sprites/blank.png");
	player->images['0'] = mlx_texture_to_image(player->mlx, new_texture);
	mlx_delete_texture(new_texture);

	for (unsigned char letter = 'a'; letter <= 'z'; letter++)
	{
		char *name = gen_name(letter);
		mlx_texture_t *new_texture = mlx_load_png(name);
		player->images[letter] = mlx_texture_to_image(player->mlx, new_texture);
		mlx_delete_texture(new_texture);
		free(name);
	}
}

void	mlx_stuff(t_player *player)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx();
	player->mlx = mlx;
	load_textures(player);
	img = mlx_new_image(mlx, BOARD_WIDTH * 64, BOARD_HEIGHT * 64);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	player->img = img;
	drawn_map(player);
	mlx_key_hook(mlx, my_key_hook, player);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

int main(int argc, char **argv)
{
    (void)argc, (void)argv;
    if (argc != 2)
        ft_error("Invalid number of arguments.");

    if (ft_strlen(argv[1]) > 1 || ft_isalpha(argv[1][0]) == 0)
        ft_error("Player team must be a letter.");

    printf("Hello, this is a player!!\n");

    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED)
    {
        perror("sem");
        exit(1);
    }

    int sem_value;
    if (sem_getvalue(sem, &sem_value) == 0)
        printf("Current semaphore value: %d\n", sem_value);
    else
    {
        perror("sem_getvalue failed");
        exit(1);
    }

    printf("sizeof(t_shared) = %ld\n", sizeof(t_shared));
    sem_wait(sem);
    void *memory_block = attach_memory_block(FILENAME, sizeof(t_shared), true);
    if (memory_block == NULL)
    {
        ft_error("Can't load shared memory.");
    }
    t_shared *game = (t_shared *)memory_block;

    if (game->players != 42)
    {
        game->players = 42;
        game->paint = 1;
        fill_board(game);
    }
    t_player player;

    ft_memset(&player, 0, sizeof(t_player));
    player.sem = sem;
    set_random_player_pos(game, &player);
    printf("new player pos: (%d,%d)\n", player.x, player.y);

    game->board[player.y][player.x] = ft_tolower(argv[1][0]);
    game->paint = 1;
    printf("writing {%s} into memory\n", argv[1]);
    sprintf(game->msg, "%s", argv[1]);
    printf("dettach: %d\n", dettach_memory_block(memory_block));
    sem_post(sem);
    mlx_stuff(&player);
    sem_close(sem);
}
