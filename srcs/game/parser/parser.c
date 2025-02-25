/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:45:44 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/25 12:45:45 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GAME.h"

char	parser(int argc, char **argv)
{
	if (argc != 2)
		ft_error("Invalid number of arguments.");
	if (ft_strlen(argv[1]) > 1 || ft_isalpha(argv[1][0]) == 0)
		ft_error("Player team must be a letter.");
	return (ft_tolower(argv[1][0]));
}
