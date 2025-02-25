/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:46:41 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 12:48:25 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

void	init_semaphores(t_game *game)
{
	sem_t	*sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
	int		sem_value;

	if (sem == SEM_FAILED)
		ft_perror("sem");
	if (sem_getvalue(sem, &sem_value) == 0)
		printf("Current semaphore value: %d\n", sem_value);
	else
		ft_perror("sem_getvalue");
	game->sem = sem;
}

t_shared	*attach_or_create_shared_memory(void)
{
	void	*memory_block = attach_memory_block(FILENAME, sizeof(t_shared), true);

	if (memory_block == NULL)
		ft_error("Can't load shared memory.");
	return (((t_shared *)memory_block));
}
