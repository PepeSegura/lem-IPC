/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DISPLAY.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:42:44 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/06 16:35:43 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "shared.h"


# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>


# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define TEXTURES_COUNT 37

typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*images[255];
	t_shared		*shared;
	sem_t			*sem;
}	t_display;


mlx_t	*init_and_customize_mlx(void);
void	load_textures(t_display *display);

/* Hooks and tools */

void	my_key_hook(mlx_key_data_t keydata, void *param);
// bool	number_in_array(int len, const int array[len], int to_find);

// /* errors.c */
// void		ft_perror(char *msg);
// void		ft_error(char *str);

#endif
