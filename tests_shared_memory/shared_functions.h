#ifndef SHARED_FUNCTIONS_H
# define SHARED_FUNCTIONS_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>

# define FILENAME       "Makefile"
# define BLOCK_SIZE     1024

# define BOARD_WIDTH    10
# define BOARD_HEIGHT   5

typedef struct s_game
{
    int players;
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    char msg[BLOCK_SIZE];
} t_game;

void	ft_perror(char *msg);
void	ft_error(char *str);

void    *attach_memory_block(char *filename, int size);
int     dettach_memory_block(char *memory_block);
int     destroy_memory_block(char *filename);

#endif
