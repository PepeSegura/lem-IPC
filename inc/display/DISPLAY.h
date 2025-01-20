/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DISPLAY.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:42:44 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/20 14:45:31 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "shared.h"
# include "keys.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>


# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

enum s_letters {
	BLANK,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
};

# define TEXTURES_COUNT 37

typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*images[255];
	t_shared		*data;
}	t_display;


/* Hooks and tools */

void	my_key_hook(mlx_key_data_t keydata, void *param);
bool	number_in_array(int len, const int array[len], int to_find);

/* errors.c */
void		ft_perror(char *msg);
void		ft_error(char *str);

#endif
