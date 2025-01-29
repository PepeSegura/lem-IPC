/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GAME.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:27:01 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/29 18:49:52 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "shared.h"

# include <time.h>
# include <sys/time.h>

typedef struct s_game
{
    mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*images[4];
    int x;
    int y;
    int status;
    sem_t *sem;
} t_game;


/* parser */
char    parser(int argc, char **argv);

/* init_game */
void    init_game(t_shared *shared);
void    init_semaphores(t_game *game);
t_shared    *attach_or_create_shared_memory(void);

/* init_player */
void init_player(t_game *player, t_shared *shared, char team_name);

/* mlx */
mlx_t	*init_and_customize_mlx(void);

void	my_key_hook(mlx_key_data_t keydata, void *param);
void	load_textures(t_game *player);


#endif
