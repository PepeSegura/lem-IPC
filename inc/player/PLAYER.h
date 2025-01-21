/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PLAYER.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:27:01 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/21 20:03:00 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "shared.h"

# include <time.h>
# include <sys/time.h>

typedef struct s_player
{
    int x;
    int y;
    int status;
    sem_t *sem;
} t_player;


#endif
