/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:00:33 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 15:23:40 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

int end_program;

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
