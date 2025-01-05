/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DISPLAY.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:42:44 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/05 21:47:36 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "shared.h"
# include "libft.h"
# include "keys.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>


# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define R 3
# define G 2
# define B 1
# define A 0
# define ABGR 4

typedef union u_color
{
	uint32_t	color;
	uint8_t		channels[ABGR];
}	t_color;

typedef struct s_map
{
}	t_map;

typedef struct s_display
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_display;


/* Hooks and tools */

void	my_key_hook(mlx_key_data_t keydata, void *param);
bool	number_in_array(int len, const int array[len], int to_find);

/* errors.c */
void		ft_perror(char *msg);
void		ft_error(char *str);

#endif
