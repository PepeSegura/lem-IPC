/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:48:36 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 16:01:25 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

char	*gen_filename(char letter)
{
	return (ft_ultrajoin("sprites/", (char [2]){letter, '\0'}, ".png", NULL));
}

void	*load_textures(t_game *player)
{
	player->images[WALL] = mlx_load_img(player->mlx, "sprites/wall.png");
	if (player->images[WALL] == NULL)
		return (NULL);
	player->images['0'] = mlx_load_img(player->mlx, "sprites/blank.png");
	if (player->images['0'] == NULL)
		return (NULL);
	for (unsigned char letter = 'a'; letter <= 'z'; letter++)
	{
		char	*name = gen_filename(letter);
		player->images[letter] = mlx_load_img(player->mlx, name);
		free(name);
		if (player->images[letter] == NULL)
			return (NULL);
	}
	return ((void *)1);
}

mlx_t	*init_and_customize_mlx(char *team_name)
{
	mlx_t				*mlx;
	mlx_win_cursor_t	*cursor;

	mlx = mlx_init(TILE * 3, TILE * 4, team_name, false);
	free(team_name);
	if (mlx == NULL)
		ft_error("Can't load mlx");
	cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(mlx, cursor);
	return (mlx);
}
