/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:40:38 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 15:27:47 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	main(void)
{
	sem_t	*sem = sem_open(SEM_NAME, O_WRONLY);

	if (sem != SEM_FAILED)
	{
		if (sem_close(sem) == -1)
			perror("sem_close");
		if (sem_unlink(SEM_NAME) == -1)
			perror("sem_unlink");
	}
	if (destroy_memory_block(FILENAME, false) == 0)
		printf("destroyed shared_mem\n");
}
