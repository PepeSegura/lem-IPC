#ifndef SHARED_H
# define SHARED_H

# include "libft.h"
# include "MLX42/MLX42.h"

# include <fcntl.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/stat.h>

# define BOARD_WIDTH    10
# define BOARD_HEIGHT   10

# define BLOCK_SIZE     1024
# define FILENAME       "Makefile"

# define SEM_NAME       "/sem_name"

typedef struct s_shared
{
    int started;
    int players;
    int paint;
    int display_pid;
    char board[BOARD_HEIGHT][BOARD_WIDTH + 1];
    char msg[BLOCK_SIZE];
} t_shared;

mlx_image_t *mlx_load_img(mlx_t *mlx, char *name);
bool        number_in_array(int len, const int array[len], int to_find);

void	ft_perror(char *msg);
void	ft_error(char *str);
void    ft_mlx_error(void);

void    *attach_memory_block(char *filename, int size, bool create);
int     dettach_memory_block(char *memory_block);
int     destroy_memory_block(char *filename, bool create);

#endif
