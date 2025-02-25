/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:15:33 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 15:15:34 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

void load_shared_memory(t_display *display)
{
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
	if (display->sem == (void *)-1)
		perror("sem");
	sem_wait(display->sem);
	t_shared *shared = (t_shared *)memory_block;
	display->shared = shared;
	display->shared->paint = 1;
	display->shared->display_pid = getpid();
	sem_post(display->sem);
}
