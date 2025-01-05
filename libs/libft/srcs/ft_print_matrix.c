/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:42:16 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 02:34:02 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_matrix(char **matrix, char *str)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		ft_printf("%s [%d] -> [%s]\n", str, i, matrix[i]);
		i++;
	}
}
