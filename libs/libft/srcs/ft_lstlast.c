/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:03:00 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 02:34:07 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Ft_lstlast returns the last element of a linked list.
 * 
 * @param lst The list to be searched.
 * 
 * @return The last element of the list. 
 */
t_list	*ft_lstlast(t_list *lst)
{
	ft_printf("pointer -> %p\n", lst);
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
