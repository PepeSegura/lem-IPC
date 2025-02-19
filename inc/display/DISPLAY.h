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
	mlx_image_t		*images[256];
	t_shared		*shared;
	sem_t			*sem;
}	t_display;


extern int	end_program;

mlx_t	*init_and_customize_mlx(void);
void	*load_textures(t_display *display);

/* Hooks and tools */
void	my_key_hook(mlx_key_data_t keydata, void *param);
void	close_display(t_display *display);
void	*close_board(t_display *display);

#endif
