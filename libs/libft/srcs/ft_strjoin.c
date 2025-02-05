/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:57:11 by psegura-          #+#    #+#             */
/*   Updated: 2025/02/05 17:35:29 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL && s2)
		return (ft_strdup(s2));
	if (s2 == NULL && s1)
		return (ft_strdup(s1));
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

char	*ft_ultrajoin(char *first, ...)
{
	va_list	list;
	char	*result;
	char	*tmp;
	char	*next;

	if (first == NULL)
		return (NULL);
	result = ft_strdup(first);
	if (!result)
		return (NULL);
	va_start(list, first);
	while (1)
	{
		next = va_arg(list, char *);
		if (next == NULL)
			break ;
		tmp = ft_strjoin(result, next);
		free(result);
		result = tmp;
	}
	va_end(list);
	return (result);
}
