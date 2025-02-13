/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:03:54 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/13 15:05:23 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*newptr;
	size_t	ptrsize;

	if (ptr == 0)
		return (malloc(size));
	ptrsize = sizeof(ptr);
	if (size <= ptrsize)
		return (ptr);
	newptr = malloc(size);
	ft_memcpy(ptr, newptr, ptrsize);
	free(ptr);
	return (newptr);
}
