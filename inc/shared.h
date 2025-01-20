/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:27:37 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/20 14:45:33 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "libft.h"

# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>

# define BOARD_WIDTH    30
# define BOARD_HEIGHT   30

# define BLOCK_SIZE     1024
# define FILENAME       "Makefile"

typedef struct s_shared
{
    int players;
    char board[BOARD_HEIGHT][BOARD_WIDTH + 1];
    char msg[BLOCK_SIZE];
} t_shared;


void	ft_perror(char *msg);
void	ft_error(char *str);

void    *attach_memory_block(char *filename, int size, bool create);
int     dettach_memory_block(char *memory_block);
int     destroy_memory_block(char *filename);

#endif