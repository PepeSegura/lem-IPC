/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:01:43 by psegura-          #+#    #+#             */
/*   Updated: 2025/01/05 20:57:19 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DISPLAY.h"

bool	number_in_array(int len, const int array[len], int to_find)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (array[i] == to_find)
			return (true);
		i++;
	}
	return (false);
}
