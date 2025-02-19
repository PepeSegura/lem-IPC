#include "DISPLAY.h"

int end_program;

void draw_map(t_display *display)
{
	int i, j, letter;

	i = 0;
	sem_wait(display->sem);
	if (display->shared->paint == 0)
	{
		sem_post(display->sem);
		return ;
	}
	while (i < BOARD_HEIGHT)
	{
		j = 0;
		while (j < BOARD_WIDTH)
		{
			letter = display->shared->board[i][j];
			mlx_image_to_window(display->mlx, display->images[letter], j * 64, i * 64);
			j++;
		}
		i++;
	}
	display->shared->paint = 0;
	sem_post(display->sem);
}

void loop_hook(void *param)
{
	static double	time = 0.0;
	t_display		*display;

	display = (t_display *)param;
	time += display->mlx->delta_time;
	if (time >= 0.5)
	{
		if (end_program == true)
			close_display(display);
		time = 0.0;
		draw_map(display);
	}
}

void	mlx_stuff(t_display *display)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx();
	display->mlx = mlx;
	if (load_textures(display) == NULL)
		close_board(display);
	img = mlx_new_image(mlx, BOARD_WIDTH * 64, BOARD_HEIGHT * 64);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	display->img = img;
	draw_map(display);
	mlx_key_hook(mlx, my_key_hook, display);
	mlx_loop_hook(mlx, loop_hook, display);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void print_board(t_shared *game)
{
	if (game->started == 0)
		ft_error("Empty map.");
	for (int i = 0; i < BOARD_HEIGHT; i++)
		printf("%s\n", game->board[i]);
}

void load_shared_memory(t_display *display)
{
	(void)display;
	void *memory_block;

	for (int i = 1; i <= 60; i++)
	{
		memory_block = attach_memory_block(FILENAME, sizeof(t_shared), false);
		if (memory_block == NULL)
		{
			if (i == 60)
				exit(1);
			dprintf(1, "%d/60: Trying to load shared memory, launch a player to generate the board.\n", i);
			usleep(1000 * 1000);
		}
		else
			break;
	}

	display->sem = sem_open(SEM_NAME, O_WRONLY);
	perror("sem");
	sem_wait(display->sem);
	t_shared *shared = (t_shared *)memory_block;
	printf("players: %d\n", shared->players);
	print_board(shared);
	printf("MSG: {%s}\n", shared->msg);
	display->shared = shared;
	display->shared->paint = 1;
	display->shared->display_pid = getpid();
	sem_post(display->sem);
}

void signal_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		printf("CLOSING DISPLAY\n");
		end_program = true;
	}
}

int	main(void)
{
	end_program = false;
	signal(SIGUSR1, signal_handler);
	t_display display;

	ft_memset(&display, 0, sizeof(t_display));
	load_shared_memory(&display);
	mlx_stuff(&display);
	exit(EXIT_SUCCESS);
}
