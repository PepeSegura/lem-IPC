#ifndef GAME_H
# define GAME_H

# include "shared.h"
# include <sys/time.h>
# include <time.h>

# define TILE 64
# define WALL 0

typedef struct s_pos
{
	int			y;
	int			x;
}				t_pos;

typedef struct s_msg
{
	long		mtype;
	int			y;
	int			x;
}				t_msg;

typedef struct s_game
{
	char			team_name;

	bool			hunt_mode;

	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*str_img;
	mlx_image_t		*images[256];

	t_pos		opponent;
	int			y;
	int			x;
	int			status;
	sem_t		*sem;
	int			queue_id;
	int			own_pid;
	t_shared	*shared;
}				t_game;

extern int		exit_signal;

/* parser */
char			parser(int argc, char **argv);

/* init_game */
void			init_game(t_shared *shared);
void			init_semaphores(t_game *game);
t_shared		*attach_or_create_shared_memory(void);

void			set_team_master(t_game *game);

/* init_player */
char			*get_player_pos(int x, int y);
void			init_player(t_game *player, t_shared *shared, char team_name);

/* mlx */
mlx_t			*init_and_customize_mlx(char *team_name);
void			draw_minimap(t_game *game);

void			my_key_hook(mlx_key_data_t keydata, void *param);
void			*load_textures(t_game *player);

void			close_player(t_game *game);
void			leave_board(t_game *game);

bool			movement(t_game *game, int key);
void			chase_opponent(t_game *game);


/* opponents */
void				find_nearest_oponent(t_game *game_data);

#endif
